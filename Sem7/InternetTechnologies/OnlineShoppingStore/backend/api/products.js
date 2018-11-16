const express = require('express')
const _ = require('lodash')
const jwt = require('jwt-simple');
const router = express.Router()
const config = require('config')
const ProductsModel = require('../models/products')
const PAGE_LIMIT = 80


router.get('/', async (req, res) => {

  // Check logged in user
  const token = req.headers.authorization
  if (token) {
    const userInfo = jwt.decode(token, config.jwt.secret);
  }

  // Parse query
  let query = _.defaults(req.query, {
    p: 1,
    sort: 'arrival'
  })

  // Find sortKey
  let sortKey = {}
  switch (query.sort) {
    case 'arrival':
      sortKey = { 'New Arrival': -1 }
      break
    case 'discounted':
      sortKey = { 'Discount Percent': -1 }
      break
  }


  // Send the response
  const products = ProductsModel.find({}, {
    '_id': 0,
    'Handle': 1,
    'Title': 1,
    'Body (HTML)': 1,
    'Discount Percent': 1,
    'New Arrival': 1,
    'Image Src': 1,
    'Variant Price': 1
  })
    .sort(sortKey)
    .skip(PAGE_LIMIT * (query.p - 1))
    .limit(PAGE_LIMIT)


  res.json({
    status: 'success',
    message: 'Logged In',
    data: await products
  });
})

module.exports = router