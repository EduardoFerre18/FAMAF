# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Copyright 2014 Carlos Bederián
# $Id: connection.py 455 2011-05-01 00:32:09Z carlos $

import socket
from constants import *
from base64 import b64encode
import time 
import os


class Connection(object):
    """
    Conexión punto a punto entre el servidor y un cliente.
    Se encarga de satisfacer los pedidos del cliente hasta
    que termina la conexión.
    """

    def __init__(self, socket, directory):
        self.directory = directory
        self.socket = socket
        self.buffer = ''
        self.connected = True
        self.status = None

    def _recv(self, timeout=None):
        self.socket.settimeout(timeout)
        data = self.socket.recv(4096).decode("ascii")
        self.buffer += data
        
        if (len(data) == 0):
            self.connected = False
            print("Client disconnected")

    def _send(self, message, timeout=None):
        self.socket.settimeout(timeout)
        message += EOL
        while message:
            bytes_sent = self.socket.send(message.encode("ascii"))
            assert bytes_sent > 0
            message = message[bytes_sent:]

    def read_line(self, timeout=None):
        while not EOL in self.buffer and self.connected:
            if timeout is not None:
                t1 = time.process_time()
            self._recv(timeout)
            if timeout is not None:
                t2 = time.process_time()
                timeout -= t2 - t1
                t1 = t2
        if EOL in self.buffer:
            request, self.buffer = self.buffer.split(EOL, 1)
            return request.strip()
        else:
            self.connected = False
            return ""

    def read_request_line(self, timeout=None):
        request = self.read_line()

        if repr(request).count('\\n') > 0:
            self.status = BAD_EOL
            self.connected = False                                             
            self._send(f"{self.status} {error_messages[self.status]}")
        elif request != "":
            request = request.split(None)

            if request[0] == "quit":
                if len(request) > 1:
                    self.status = INVALID_ARGUMENTS
                    self._send(f"{self.status} {error_messages[self.status]}")
                else:
                    self.quit()
            elif request[0] == "get_file_listing":
                if len(request) > 1:
                    self.status = INVALID_ARGUMENTS
                    self._send(f"{self.status} {error_messages[self.status]}")
                else:
                    self.get_file_listing()
            elif request[0] == "get_metadata":
                if len(request) != 2:
                    self.status = INVALID_ARGUMENTS
                    self._send(f"{self.status} {error_messages[self.status]}")
                else:
                    self.get_metadata(request[1])
            elif request[0] == "get_slice":
                if len(request) != 4:
                    self.status = INVALID_ARGUMENTS
                    self._send(f"{self.status} {error_messages[self.status]}")
                elif not (request[2].isdigit()) and not (request[3].isdigit()):
                    self.status = INVALID_ARGUMENTS
                    self._send(f"{self.status} {error_messages[self.status]}")
                else:
                    filename, offset, size = request[1], int(
                        request[2]), int(request[3])
                    self.get_slice(filename, offset, size)
            else:
                self.status = INVALID_COMMAND
                self._send(f"{self.status} {error_messages[self.status]}")

    def get_file_listing(self):
        file_list = os.listdir(self.directory)
        self.status = CODE_OK
        response = f"{self.status} {error_messages[self.status]}{EOL}"
        for file in file_list:
            response += (file + EOL)
        self._send(response)

    def get_metadata(self, filename):
        file_path = os.path.join(self.directory, filename)

        if not os.path.exists(file_path):
            self.status = FILE_NOT_FOUND
            self._send(f"{self.status} {error_messages[self.status]}")
            return

        file_size = os.path.getsize(file_path)
        self.status = CODE_OK
        response = f"{CODE_OK} {error_messages[CODE_OK]}{EOL}{file_size}"
        self._send(response)

    def get_slice(self, filename, offset, size):
        file_path = os.path.join(self.directory, filename)
        file_size = os.path.getsize(file_path)

        if not os.path.exists(file_path):
            self.status = FILE_NOT_FOUND
            self._send(f"{self.status} {error_messages[self.status]}")
            return

        if offset < 0 or offset > file_size:
            self.status = BAD_OFFSET
            self._send(f"{self.status} {error_messages[self.status]}")
            return

        if (offset > (file_size - size)) or size < 0:
            self.status = BAD_REQUEST
            self._send(f"{self.status} {error_messages[self.status]}")
            self.connected = False
            return

        try:
            with open(file_path, 'rb') as file:
                file.seek(offset)
                data = file.read(size)
                encoded_data = b64encode(data).decode('ascii')
                self.status = CODE_OK
                response = f"{CODE_OK} {error_messages[CODE_OK]}{EOL}{encoded_data}"
                self._send(response)
        except Exception as e:
            self.status = INTERNAL_ERROR
            self._send(f"{self.status} {error_messages[self.status]}")

    def quit(self):
        self.status = CODE_OK
        self.connected = False
        response = f"{self.status} {error_messages[self.status]}"
        self._send(response)
        self.socket.close()

    def handle(self):
        """
        Atiende eventos de la conexión hasta que termina.
        """
        while self.connected:
            self.read_request_line()
        self.socket.close()
