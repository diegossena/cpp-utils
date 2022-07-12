const http = require('http')

http
  .createServer(async (request, response) => {
    await new Promise((resolve, reject) => {
      request.on('data', chunk => console.log(chunk))
      request.on('end', () => {
        console.log('end')
        resolve()
      })
    })
    response.end('test')
  })
  .listen(8002, () => console.log('listening'))