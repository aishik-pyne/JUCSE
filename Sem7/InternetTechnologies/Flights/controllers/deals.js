const DealsModel = require('../models/deals')
const _ = require('lodash')
module.exports = {
    list: async () => {
        return await DealsModel.find()
    },
    create: async ({name, discountPercent}) => {
        return await DealsModel.create({
            name,
            discountPercent,
        })
        
    },
    
}