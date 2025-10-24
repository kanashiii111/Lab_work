const express = require('express')
const path = require('path')
const bodyParser = require('body-parser')
const app = express()
const port = 3000
app.use(express.static(path.join(__dirname, '../css')))
app.use("/js", express.static(path.join(__dirname, '../js')))
app.use(bodyParser.urlencoded({extended: true}));

orders = []

app.get('/orders', (req, res) => {
    res.send(orders)
})

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../index.html'))
})

app.listen(port, () => {
    console.log(`app listening on port ${port}`)
})

app.post('/', (req, res) => {
    data = req.body
    orders.push(data)
})