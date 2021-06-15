#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <zmq.hpp>

void StartVicon() {
  zmq::context_t context(1);

  zmq::socket_t vicon_socket(context, ZMQ_PUB);
  vicon_socket.bind("tcp://*:5555");

  for (int iteration = 0;; ++iteration) {
    zmq::message_t vicon_data(2 * 16 * sizeof(double));
    double *vicon_data_d = vicon_data.data<double>();
    for (int i = 0; i < 32; ++i) {
      vicon_data_d[i] = i + iteration;
    }
    vicon_socket.send(vicon_data, zmq::send_flags::none);

    sleep(1);
  }
}

void StartRobot() {
  zmq::context_t context(1);

  zmq::socket_t command_socket(context, ZMQ_SUB);
  command_socket.set(zmq::sockopt::subscribe, "");
  command_socket.bind("tcp://*:5556");

  while (true) {
    zmq::message_t command_data(6 * sizeof(double));
    auto rc = command_socket.recv(command_data, zmq::recv_flags::none);
    for (int i = 0; i < 6; ++i) {
      std::cout << command_data.data<double>()[i] << ", ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::thread robot(StartRobot);
  std::thread vicon(StartVicon);

  vicon.join();
  robot.join();

  return 0;
}
