const express = require('express')
const router = express.Router()
const userRouter = require('./users')
const productRouter = require('./products')
const _ = require('lodash')

router.use('/users', userRouter)
router.use('/products',productRouter)
module.exports = router