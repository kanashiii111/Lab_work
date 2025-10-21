const express = require('express')
const path = require('path')
const bodyParser = require('body-parser')
//инициализируем приложение
const app = express()
const port = 3000
//подключаем статические файлы
app.use(express.static(path.join(__dirname, '../css')))
app.use(bodyParser.urlencoded({extended: true}));

//создаем переменную для хранения данных
const list = []

//возвращаем данные по запросу
app.get('/list', (req, res) => {
    res.send(list)
})

//выводим файл index.html
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '../index.html'))
})

//слушаем порт 3000
app.listen(port, () => {
    console.log(`app listening on port ${port}`)
})

//добавляем в массив новые данные
app.post('/', (req, res) => {

    //передаем данные в массив
    list.push(req.body)

    //возвращаем ответ
    res.send('Данные добавлены')
})
