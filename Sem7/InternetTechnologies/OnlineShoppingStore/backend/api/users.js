const express = require('express')
const Joi = require('joi')
const jwt = require('jwt-simple');
const router = express.Router()
const config = require('config')
const UserModel = require('../models/users')



router.post('/register', async (req, res) => {
  const data = req.body;
  const schema = Joi.object().keys({
    email: Joi.string().email().required(),
    password: Joi.string().required(),
    gender: Joi.string().valid('Male', 'Female')
  });
  Joi.validate(data, schema, (err, value) => {
    if (err) {
      res.status(422).json({
        status: 'error',
        message: 'Invalid request data',
        data: data
      });
    } else {
      let newUser = new UserModel({ email: value.email, gender: value.gender })
      newUser.password = newUser.generateHash(value.password);
      newUser.save()
      res.json({
        status: 'success',
        message: 'User created successfully',
        data: { email: newUser.email }
      });
    }

  });
})

router.post('/login', async (req, res) => {
  const data = req.body;
  const schema = Joi.object().keys({
    email: Joi.string().email().required(),
    password: Joi.string().required()
  });
  Joi.validate(data, schema, (err, value) => {
    if (err) {
      res.status(422).json({
        status: 'error',
        message: 'Invalid request data',
        data: data
      });
    } else {
      UserModel.findOne({ email: value.email }, function (err, user) {
        if (!user.validPassword(req.body.password)) {
          res.status(401).json({
            status: 'error',
            message: 'Invalid Credentials',
            data: data
          });
        } else {
          const payload = { email: user.email, gender: user.gender };
          const token = jwt.encode(payload, config.jwt.secret);
          res.json({
            status: 'success',
            message: 'Logged In',
            data: {
              email: user.email,
              token: token
            }
          });
        }
      });
    }

  });
})

module.exports = router