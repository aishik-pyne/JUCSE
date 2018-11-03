const mongoose = require('mongoose')
const FlightsSchema = mongoose.Schema({
    name: String,
    source: String,
    destination: String,
    departure: String,
    cost: Number,
    deal: {
        type: mongoose.Schema.Types.ObjectId,
        ref: 'Deals'
    }
}, {
    collection: 'Flights'
})
module.exports = mongoose.model('Flights', FlightsSchema)