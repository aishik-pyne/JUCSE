import os
import random
import tensorflow as tf
import time
from datetime import datetime
import pandas as pd
import numpy as np
import cv2


class CNN:
    def __init__(self, num_classes=10, display_step=20, validate_step=100, save_step = 1000,
                use_cpu=False, checkpoint_dir='./fashion_checkpoints/'):
        self.display_step =display_step
        self.validate_step = validate_step
        self.use_cpu = use_cpu
        self.checkpoint_dir = checkpoint_dir

        self.NUM_CLASSES = num_classes

        self.build()
        self.load_data()
        self.sess = tf.Session()
        self.sess.run(tf.global_variables_initializer())
        self.saver = tf.train.Saver(max_to_keep=1)
        self.variable_summaries()

    def variable_summaries(self):
        """Attach a lot of summaries to a Tensor (for TensorBoard visualization)."""
        with tf.name_scope('summaries'):
            tf.summary.scalar('loss', self.loss)
            tf.summary.scalar('learning_rate', self.rate)
            tf.summary.scalar('accuracy', self.accuracy)
        self.merged = tf.summary.merge_all()
        self.train_writer = tf.summary.FileWriter(self.checkpoint_dir,
                                      self.sess.graph)

    def save_session(self):
        print("{} Saving checkpoint of model...".format(datetime.now()))

        # save checkpoint of the model
        checkpoint_name = os.path.join(self.checkpoint_dir,
                                       'fashion-model-iterations')
        save_path = self.saver.save(self.sess, checkpoint_name, global_step=self.sess.run(self.global_step))

        print("{} Model checkpoint saved at {}".format(datetime.now(),
                                                       save_path))

    def restore_session(self):
        if not os.path.exists(self.checkpoint_dir):
            raise IOError(self.checkpoint_dir + ' does not exist.')
        else:
            path = tf.train.get_checkpoint_state(self.checkpoint_dir)
            if path != None:
                self.saver.restore(self.sess,tf.train.latest_checkpoint(self.checkpoint_dir))

    def predict(self, image):
        self.restore_session()
        return self.prediction.eval(session=self.sess, feed_dict={self.x: [cv2.resize(image, (28, 28))], self.keep_prob: 1.0})[0]

    def load_data(self):
        train_data = np.array(pd.read_csv('data/fashion-mnist_train.csv', header = None))
        self.val_data = train_data[:10000]
        self.train_data = train_data[10000:]
        self.test_data = np.array(pd.read_csv('data/fashion-mnist_test.csv', header = None))
        print('Train Data :'+str(self.train_data.shape))
        print('Val Data :'+str(self.val_data.shape))
        print('Test Data :'+str(self.test_data.shape))

    def data_generator(self, mode='train', batch_size=64):
        if mode == 'train':
            choice = np.random.choice(self.train_data.shape[0], size=batch_size, replace=False)
            batch = self.train_data[choice]
            return batch[:, 1:].reshape((-1,28,28,1)), np.eye(10)[batch[:, 0]]
        if mode == 'val':
            choice = np.random.choice(self.val_data.shape[0], size=batch_size, replace=False)
            batch = self.val_data[choice]
            return batch[:, 1:].reshape((-1,28,28,1)), np.eye(10)[batch[:, 0]]
        if mode == 'test':
            choice = np.random.choice(self.test_data.shape[0], size=batch_size, replace=False)
            batch = self.test_data[choice]
            return batch[:, 1:].reshape((-1,28,28,1)), np.eye(10)[batch[:, 0]]

    def train(self, iterations=1000, restore_session=True, learning_rate=1e-6):
        if restore_session:
            self.restore_session()
        start_time = time.time()

        for iter in np.arange(iterations):
            global_step = tf.train.global_step(self.sess, self.global_step)
            x, y = self.data_generator()
            _, loss, summary = self.sess.run(fetches=[self.train_step, self.loss, self.merged],
                                            feed_dict={ self.x: x,
                                                        self.y: y,
                                                        self.rate: learning_rate,
                                                        self.keep_prob: 0.5})
            self.train_writer.add_summary(summary, global_step=global_step)
            if iter % self.display_step == 0:
                print('step {} global_step {} finished in {:.2f} s loss = {}'.format(iter, global_step, time.time() - start_time, loss))
                start_time = time.time()
            if iter % self.validate_step == 0:
                self.validate()
            if global_step % 1000 == 0:
                self.save_session()
        self.validate()
        self.save_session()

    def validate(self):
        acc_val = 0
        acc_train = 0
        for iter in np.arange(20):
            x, y = self.data_generator(mode='val')
            acc_val += self.sess.run(self.accuracy, feed_dict={self.x: x, self.y: y, self.keep_prob:1})
            x, y = self.data_generator(mode='train')
            acc_train += self.sess.run(self.accuracy, feed_dict={self.x: x, self.y: y, self.keep_prob:1})
        acc_val /= 20
        acc_train /=20
        print('Training accuracy at global_step {} is {} %'.format(tf.train.global_step(self.sess, self.global_step), acc_train*100))
        print('Validation accuracy at global_step {} is {} %'.format(tf.train.global_step(self.sess, self.global_step), acc_val*100))

    def build(self):
        if self.use_cpu:
            device = '/cpu:0'
        else:
            device = '/gpu:0'

        self.global_step = tf.Variable(0, trainable=False, name='global_step')
        with tf.device(device):
            """Create the network graph."""
            # Input tensors
            self.x = tf.placeholder(tf.float32, shape=(None, 28, 28, 1))
            self.y = tf.placeholder(tf.int64, shape=(None, self.NUM_CLASSES))
            self.rate = tf.placeholder(tf.float32, shape=[])
            self.keep_prob = tf.placeholder(tf.float32)

            # 1st Layer: Conv (w ReLu) -> Pool -> Lrn
            conv1 = self.conv(self.x, 5, 5, 96, 1, 1, padding='VALID', name='conv1')
            print('conv1'+str(conv1.get_shape()))

            # 2nd Layer: Conv (w ReLu) -> Pool -> Lrn with 2 groups
            conv2 = self.conv(conv1, 3, 3, 256, 1, 1, name='conv2')
            pool2 = self.max_pool(conv2, 2, 2, 2, 2, padding='VALID', name='pool2')
            norm2 = self.lrn(pool2, 2, 2e-05, 0.75, name='norm2')
            print('conv2'+str(conv2.get_shape()))
            print('pool2'+str(pool2.get_shape()))
            print('norm2'+str(norm2.get_shape()))

            # 3rd Layer: Conv (w ReLu) splitted into two groups
            conv3 = self.conv(norm2, 3, 3, 384, 1, 1, padding='VALID', name='conv3')
            print('conv3'+str(conv3.get_shape()))

            # 4th Layer: Conv (w ReLu) -> Pool splitted into two groups
            conv4 = self.conv(conv3, 3, 3, 384, 1, 1, name='conv4')
            pool4 = self.max_pool(conv4, 2, 2, 2, 2, padding='SAME', name='pool4')
            norm4 = self.lrn(pool4, 2, 2e-05, 0.75, name='norm4')
            print('conv4'+str(conv4.get_shape()))
            print('pool4'+str(pool4.get_shape()))

            # 5th Layer: Flatten -> FC (w ReLu) -> Dropout
            norm4_dims = int(norm4.get_shape()[1] * norm4.get_shape()[2] * norm4.get_shape()[3])
            flattened = tf.reshape(norm4, [-1, norm4_dims])
            fc5 = self.fc(flattened, norm4_dims, 1024, name='fc5')
            dropout5 = self.dropout(fc5, self.keep_prob)

            # 6th Layer: FC (w ReLu) -> Dropout
            fc6 = self.fc(dropout5, 1024, 512, name='fc6')
            dropout6 = self.dropout(fc6, self.keep_prob)

            # 7th Layer: FC (w ReLu) -> Dropout
            fc7 = self.fc(dropout6, 512, 128, name='fc7')
            dropout7 = self.dropout(fc7, self.keep_prob)

            # 8th Layer: FC and return unscaled activations
            self.fc8 = self.fc(dropout7, 128, self.NUM_CLASSES, relu=False, name='fc8')

            print('fc6'+str(fc6.get_shape()))
            print('fc7'+str(fc7.get_shape()))
            print('fc8'+str(self.fc8.get_shape()))

            # Define the loss and the accuracies
            self.loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=self.fc8, labels=self.y), name="cross_ent_loss")
            self.optimizer = tf.train.AdamOptimizer(self.rate)
            self.train_step = self.optimizer.minimize(loss=self.loss, global_step=self.global_step)

        self.prediction = tf.argmax(tf.nn.softmax(self.fc8), axis=-1)
        self.accuracy = tf.reduce_mean(tf.cast(tf.equal(tf.argmax(self.fc8, 1), tf.argmax(self.y, 1)), tf.float32), name="accuracy")

    def conv(self, x, filter_height, filter_width, num_filters, stride_y, stride_x, name, padding='VALID'):
        # Get number of input channels
        input_channels = int(x.get_shape()[-1])

        with tf.variable_scope(name) as scope:
            # Create tf variables for the weights and biases of the conv layer
            weights = tf.get_variable('weights', shape=[filter_height,
                                                        filter_width,
                                                        input_channels,
                                                        num_filters])
            biases = tf.get_variable('biases', shape=[num_filters])

        return tf.nn.relu(tf.nn.conv2d(input=x, filter=weights, strides=[1, stride_y, stride_x, 1],padding=padding)+biases)

    def fc(self, x, num_in, num_out, name, relu=True):
        """Create a fully connected layer."""
        with tf.variable_scope(name) as scope:

            # Create tf variables for the weights and biases
            weights = tf.get_variable('weights', shape=[num_in, num_out],
                                      trainable=True)
            biases = tf.get_variable('biases', [num_out], trainable=True)

            # Matrix multiply weights and inputs and add bias
            act = tf.nn.xw_plus_b(x, weights, biases, name=scope.name)

        if relu:
            # Apply ReLu non linearity
            relu = tf.nn.relu(act)
            return relu
        else:
            return act

    def max_pool(self, x, filter_height, filter_width, stride_y, stride_x, name,
                 padding='SAME'):
        """Create a max pooling layer."""
        return tf.nn.max_pool(x, ksize=[1, filter_height, filter_width, 1],
                              strides=[1, stride_y, stride_x, 1],
                              padding=padding, name=name)

    def lrn(self, x, radius, alpha, beta, name, bias=1.0):
        """Create a local response normalization layer."""
        return tf.nn.local_response_normalization(x, depth_radius=radius,
                                                  alpha=alpha, beta=beta,
                                                  bias=bias, name=name)

    def dropout(self, x, keep_prob):
        """Create a dropout layer."""
        return tf.nn.dropout(x, keep_prob)

if __name__ == '__main__':
    model = CNN(validate_step=300)
    model.train(iterations=9500, restore_session=True)
