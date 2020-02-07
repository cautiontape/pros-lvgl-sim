
#include "ncrapi/device/adi.hpp"
#include "ncrapi/system/logger.hpp"
#include "ncrapi/system/sysBase.hpp"

namespace ncrapi {

ADIAnalogIn::ADIAnalogIn(const std::string &name, const int &port) : pros::ADIAnalogIn(port),
                                                                     _port(port),
                                                                     _name(name)

{
    sysData->adiCheck(_port, _name);
    logger->info({_name, ":", std::to_string(_port), "构造成功"});
}
ADIAnalogIn::ADIAnalogIn(const std::string &name, const json &pragma) : pros::ADIAnalogIn(pragma[name].get<int>()),
                                                                        _port(pragma[name].get<int>()),
                                                                        _name(name)

{
    sysData->adiCheck(_port, _name);
    logger->info({_name, ":", std::to_string(_port), "构造成功"});
}

std::string ADIAnalogIn::getName()
{
    return _name;
}
int ADIAnalogIn::getPort()
{
    return _port;
}

ADIDigitalIn::ADIDigitalIn(const std::string &name, const int &port) : pros::ADIDigitalIn(port),
                                                                       _port(port),
                                                                       _name(name)
{
    sysData->adiCheck(_port, _name);
    logger->info({_name, ":", std::to_string(_port), "构造成功"});
}

ADIDigitalIn::ADIDigitalIn(const std::string &name, const json &pragma) : pros::ADIDigitalIn(pragma[name].get<int>()),
                                                                          _port(pragma[name].get<int>()),
                                                                          _name(name)
{
    sysData->adiCheck(_port, _name);
    logger->info({_name, ":", std::to_string(_port), "构造成功"});
}
std::string ADIDigitalIn::getName()
{
    return _name;
}
int ADIDigitalIn::getPort()
{
    return _port;
}

ADIEncoder::ADIEncoder(const std::string &name, const std::pair<int, int> &port) : pros::ADIEncoder(port.first, port.second),
                                                                                   _port(port),
                                                                                   _name(name)
{
    sysData->adiCheck(_port, _name);
    logger->info({_name, ":", std::to_string(_port.first), " ", std::to_string(_port.second), "构造成功"});
}

ADIEncoder::ADIEncoder(const std::string &name, const json &pragma) : pros::ADIEncoder(pragma[name].at(0).get<int>(), pragma[name].at(1).get<int>()),
                                                                      _port(std::make_pair<int, int>(pragma[name].at(0).get<int>(), pragma[name].at(1).get<int>())),
                                                                      _name(name)

{
    sysData->adiCheck(_port, _name);
    logger->info({_name, ":", std::to_string(_port.first), " ", std::to_string(_port.second), "构造成功"});
}
std::string ADIEncoder::getName()
{
    return _name;
}
std::pair<int, int> ADIEncoder::getPort()
{
    return _port;
}

} // namespace ncrapi