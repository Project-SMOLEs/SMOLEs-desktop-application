#include "SmolesManager.h"

#include <iostream>

SmolesManager::SmolesManager()
{
}

SmolesManager::~SmolesManager()
{
}

void SmolesManager::set_bluetooth_address(const std::string &_address)
{
  std::cout << "Bluetooth address: " << _address << "\n";
}

void SmolesManager::connect()
{
  std::cout << "Connecting to bluetooth device.\n";
}

void SmolesManager::disconnect()
{
  std::cout << "Disconnect from bluetooth device.\n";
}

void SmolesManager::start_measuring()
{
  std::cout << "Start measurement.\n";
}

void SmolesManager::stop_measuring()
{
  std::cout << "Stop measurement.\n";
}

void SmolesManager::set_data_storage_path(const std::string &_path)
{
  std::cout << "Data stored at " << _path << "\n";
}

void SmolesManager::start_recording()
{
  std::cout << "Start recording.\n";
}

void SmolesManager::stop_recording()
{
  std::cout << "Stop recording.\n";
}
