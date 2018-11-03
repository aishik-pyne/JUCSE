const mongoose = require('mongoose')
const DealsSchema = mongoose.Schema({
    name: String,
    discountPercent: Number
}, {
    collection: 'Deals'
})
module.exports = mongoose.model('Deals', DealsSchema)