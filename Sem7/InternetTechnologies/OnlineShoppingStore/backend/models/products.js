const mongoose = require('mongoose')
const ProductsSchema = mongoose.Schema({
  'Handle': String,
  'Title': String,
  'Body (HTML)': String,  
  'Discount Percent': Number,
  'New Arrival': Boolean,
  'Image Src': String,
  'Variant Price': Number
}, {
    collection: 'Products'
  })
module.exports = mongoose.model('Products', ProductsSchema)