import pandas as pd
import pymongo
import random
db = pymongo.MongoClient("mongodb://localhost:27017/")
db = db['ecomm']
productsCollection = db['Products']
productsCollection.drop()
apparel = pd.read_csv('./apparel.csv')
for idx, item in apparel.iterrows():
  data = item.to_dict()
  data['Discount Percent'] = random.randint(5, 40) if random.random() < 0.5 else 0
  data['New Arrival'] = random.choice([True, False])
  data['Type'] = 'apparel'
  insertedProduct = productsCollection.insert(data)
  print(insertedProduct)

jewelery = pd.read_csv('./jewelery.csv')
for idx, item in jewelery.iterrows():
  data = item.to_dict()
  data['Discount Percent'] = random.randint(5, 40) if random.random() < 0.5 else 0
  data['New Arrival'] = random.choice([True, False])
  data['Type'] = 'jewelery'
  insertedProduct = productsCollection.insert(data)
  print(insertedProduct)

print(list(data.keys()))