#include <string>

class SmolesManager
{
public:
  SmolesManager();
  ~SmolesManager();

  void set_bluetooth_address(const std::string &_address);
  void connect();
  void disconnect();

  void start_measuring();
  void stop_measuring();

  void set_data_storage_path(const std::string &_path);
};
