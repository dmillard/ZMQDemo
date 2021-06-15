#!/usr/bin/env python

import argparse
import numpy as np
import random
import struct
import sys
import time
import zmq

parser = argparse.ArgumentParser()
parser.add_argument("--hostname", default="172.16.0.1")
parser.add_argument("--vicon_port", type=int, default="5555")
parser.add_argument("--command_port", type=int, default="5556")
args = parser.parse_args()


def main():
    context = zmq.Context()

    vicon_socket = context.socket(zmq.SUB)
    vicon_socket.setsockopt_string(zmq.SUBSCRIBE, "")
    vicon_socket.connect(f"tcp://{args.hostname}:{args.vicon_port}")

    command_socket = context.socket(zmq.PUB)
    command_socket.connect(f"tcp://{args.hostname}:{args.command_port}")

    while True:
        vicon_msg = vicon_socket.recv()
        vicon_data = struct.unpack('32d', vicon_msg)
        
        command = np.square(np.array(vicon_data[0:6]))
        print("Sending command", command)

        command_msg = struct.pack('=6d', *command)
        command_socket.send(command_msg)

if __name__ == '__main__':
    main()
