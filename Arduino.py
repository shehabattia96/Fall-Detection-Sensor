# Shehab Attia, March 2019
# Data collection tool to collect data from arduino sensors and store data as labeled data for classification
import serial.tools.list_ports
import serial
import time
class Arduino:
    _serialConnection = None

    @staticmethod
    def findArduinoPorts():
        #References https://stackoverflow.com/a/25112066
        all_ports = list(serial.tools.list_ports.comports())
        found_ports = []
        for p in all_ports:
            if "Arduino" in p[1]:
                found_ports.append(p)
        return found_ports
    
    def serialRead(self):
        if self._serialConnection is None:
            return None
        packet = {}
        packet["time"] = time.time()
        packet["data"] = self._serialConnection.readline()
        return packet


    def makeConnection(self, port, baud = 9600):
        return serial.Serial(port,baud,timeout=5)

## TODO: Make gui, establish a connection, save labeled data