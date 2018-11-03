import pandas as pd
import json
import requests
import random
deals = [
    {
        "name": "Silver",
        "discountPercent": 20
    },
    {
        "name": "Gold",
        "discountPercent": 30
    },
    {
        "name": "Bronze",
        "discountPercent": 10
    },
]
for deal in deals:
    res = requests.post("http://localhost:15000/api/deals", json=deal, )
    print(res.text)

data = pd.read_excel('datafile.xls')
for index, item in data.iterrows():
    flight = {
        "name": "{}-{}".format(item['AIRLINE_CODE'], item['FLIGHT_NUMBER']),
        "source": item['LOCAL_AIRPORT'],
        "destination": item['SOURCE_DESTINATION'],
        "departure": str(item['SCHED_TIME']).zfill(4),
        "cost": random.randint(1000, 60000),
        "deal": random.choice([None, 'Bronze', 'Silver', 'Gold'])
    }
    print(flight)
    res = requests.post("http://localhost:15000/api/flights", json=flight, )
    print(res.text)


