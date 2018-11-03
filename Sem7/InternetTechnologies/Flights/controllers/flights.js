const FlightsModel = require('../models/flights')
const DealsModel = require('../models/deals')
const _ = require('lodash')
const PAGE_LIMIT = 60
module.exports = {
    list: async (query) => {
        query = _.defaults(query, {
            p: 1,
            sort: 'cost',
            ord: 'asc'
        })
        const filter = _.pick(query, ['source', 'destination'])
        const sortkey = query.sort
        const order = query.ord == 'asc' ? 1 : -1
        let sort = {}
        sort[sortkey] = order


        const flights = await FlightsModel.find(filter).populate('deal', {_id:0}).sort(sort).skip(PAGE_LIMIT*(query.p -1)).limit(PAGE_LIMIT)
        const totalFlights = await FlightsModel.find(filter).count()
        return {
            flights,
            pages: Math.ceil(totalFlights/PAGE_LIMIT)
        }
    },
    create: async ({name, source, destination, departure, cost, deal}) => {
        if (deal) {
            const dealRecord = await DealsModel.findOne({name: deal})
            
            return await FlightsModel.create({
                name,
                source,
                destination,
                departure,
                cost,
                deal: dealRecord._id
            })
        } else {
            return await FlightsModel.create({
                name,
                source,
                destination,
                departure,
                cost
            })

        }
        
    },
    listSources: async () => {
        return await FlightsModel.distinct('source')
    },
    listDestinations: async () => {
        return await FlightsModel.distinct('destination')
    }
}