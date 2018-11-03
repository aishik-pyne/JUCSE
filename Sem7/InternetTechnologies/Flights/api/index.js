const express = require('express')
const router = express.Router()
const _ = require('lodash')
const flightsController = require('../controllers/flights')
const dealsController = require('../controllers/deals')

router.get('/flights', async (req, res) => {
    res.json(await flightsController.list(req.query))
})
router.post('/flights', async (req, res) => {
    const flight = await flightsController.create(req.body)
    res.json(await flight)
})
router.get('/flights/sources', async (req, res) => {
    res.json(await flightsController.listSources())
})
router.get('/flights/destinations', async (req, res) => {
    res.json(await flightsController.listDestinations())
})
router.post('/deals', async (req, res) => {
    const deal = await dealsController.create(req.body)
    res.json(await deal)
})
module.exports = router