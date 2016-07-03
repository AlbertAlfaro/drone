import tornado.ioloop
import tornado.web
import tornado.websocket
from tornado.options import define, options, parse_command_line
import serial
import time
bEncontrado=False

for iPuerto in range(0, 4):
    try:
        # Puerto que vamos a probar
        PUERTO = '/dev/ttyACM' + str(iPuerto)
        # Velocidad 
        VELOCIDAD = '9600'
        # Probamos ha abrir el puerto
        Arduino = serial.Serial(PUERTO, VELOCIDAD)
        # si no se ha producido un error, cerramos el puerto
        Arduino.close()
        # cambiamos el estado del la variable para saber si lo hemos encontrado
        bEncontrado = True
        # Salimos del bucle
        break
    except:
        # Si hay error, no hacemos nada y continuamos con la busqueda
        pass
# Si encontramos el puerto?
if bEncontrado:
    # Mostramos el puerto donde esta el arduino
    print('el puerto del arduino es: ' + '/dev/ttyACM' + str(iPuerto))
    PuertoSerie = serial.Serial('/dev/ttyACM'+str(iPuerto), baudrate=9600)
else:
	print('No se ha encontrado puerto de Ardunio')
class Client:
    def __init__(self, clientId, name, cont, connection):
        self.id = clientId
        self.name = name
        self.cont = cont
        self.connection = connection 
 
clients = []
class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("index.html")
 
class WebSocketHandler(tornado.websocket.WebSocketHandler):
    def open(self, *args):
        self.id = self.get_argument("Id")
        self.accion = self.get_argument("accion")
        self.cont = self.get_argument("continue")
        newclient = True
        for client in clients:
            if client.id == self.id:
				data=''
				data+=self.accion[1]
				data=data.encode('ascii','replace')
				PuertoSerie.write(data)
				print data
				client.connection.write_message("%s" %(self.accion))
				newclient = False
				break
        if newclient:
            clientRef = Client(self.id, self.accion,self.cont, self)
            clients.append(clientRef)
            data=''
            data+=self.accion[1]
            data=data.encode('ascii','replace')
            PuertoSerie.write(data)
            time.sleep(0.1)
            print data
            self.write_message("%s" %(self.accion))
            
    def on_message(self, message):
				
        for client in clients:
            if client.id == self.id:
                print "Message from %s received : %s" % (client.name, message)
     
       
    def on_close(self):
        for client in clients:
            if self.id == client.id:
                clients.remove(client)
                break
 
define("port", default=8888, help="run on the given port", type=int)
app = tornado.web.Application([
    (r'/', IndexHandler),
    (r'/ws', WebSocketHandler),
])
 
if __name__ == '__main__':
    parse_command_line()
    app.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()

