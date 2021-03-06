
#include "ncrapi/system/sysBase.hpp"
#include "ncrapi/system/logger.hpp"

namespace ncrapi {
SysBase::SysBase(const json &pragam)
{
    if (!readSDcard(pragam))
    {
        logger->error({I18N_SYSTEM_READ_USERCONFIG});
        jsonVal = pragam;
        if (!saveData())
            logger->error({I18N_SYSTEM_SAVE_ERROR});
    }
    for (size_t i = 1; i <= 21; i++)
        _i2cPort.push_back(i); //1-21I2C端口号
    for (size_t i = 1; i <= 8; i++)
        _adiPort.push_back(i); //1-8adi端口号
    logger->info({I18N_SYSTEM I18N_BASE I18N_CREATE_SUCCESSFUL});
}

/*
 * 从SD中读取文件 存入数据容器
 * @tparam DATA 数据容器类型
 * @param data 数据容器
 * @param filePath 路径
 * @param name 名字
 */
bool SysBase::readSDcard(json pragam)
{
#if (SIM_MODE == 1)
    FILE *file = fopen("./config.json", "r");
#else
    FILE *file = fopen("/usd/config.json", "r");
#endif
    if (file == nullptr)
    {
        logger->error({I18N_SYSTEM_READ_ERROR});
        return false;
    }
    char buf[1024];
    std::string line;
    while (fgets(buf, 1024, file) != nullptr) //读取一行
        line += buf;
    jsonVal = json::parse(line);
    if (jsonVal[I18N_SYSTEM_INFO][I18N_USER].get<std::string>() != pragam[I18N_SYSTEM_INFO][I18N_USER].get<std::string>())
    {
        logger->error({I18N_SYSTEM_USER_ERROR_1});
        logger->error({I18N_SYSTEM_USER_ERROR_2, jsonVal[I18N_SYSTEM_INFO][I18N_USER].get<std::string>()});
        logger->error({I18N_SYSTEM_USER_ERROR_3, pragam[I18N_SYSTEM_INFO][I18N_USER].get<std::string>()});
        while (1)
            ;
    }
    std::stringstream oss;     //主要为了去掉小数点后多余的0 默认3位
    oss.setf(std::ios::fixed); //用定点格式显示浮点数,不会用科学计数法表示
    oss.precision(1);          //由于用了定点格式，设置变为了保留1位小数
    oss << pragam[I18N_JSON_VER];
    if (jsonVal[I18N_JSON_VER] < pragam[I18N_JSON_VER])
    {
        auto patch = json::userdiff(jsonVal, pragam); //比较差异
        jsonVal = jsonVal.patch(patch);               //应用补丁
        oss >> jsonVal[I18N_JSON_VER];
        logger->debug({I18N_SYSTEM_JSON_UPDATE_1, oss.str().c_str()});
        saveData();
    }
    else
        logger->info({I18N_SYSTEM_JSON_UPDATE_2, oss.str().c_str()});
    fclose(file);
    return true;
}
/**
 * 以vector 容器为基础修改保存文件
 * @tparam T 数据的类型
 * @param data 数据的名称
 * @param filePath  数据的路径
 * @return true 保存成功
 * @return false 保存失败
 */

bool SysBase::saveData()
{
#if (SIM_MODE == 1)
    FILE *file = fopen("./config.json", "w");
#else
    FILE *file = fopen("/usd/config.json", "w");
#endif
    if (file == nullptr)
    {
        logger->error({I18N_SYSTEM_JSON_SAVE_ERROR});
        return false;
    }
    fprintf(file, "%s", jsonVal.dump(4).c_str()); //保存
    logger->info({I18N_SYSTEM_JSON_SAVE_SUCCESSFUL});
    fclose(file);
    return true;
}
void SysBase::i2cCheck(const int port, const std::string name)
{
    for (auto it = _i2cPort.begin(); it != _i2cPort.end(); it++)
    {
        if (*it == port)
        {
            _i2cPort.erase(it);
            break;
        }
        if (it == _i2cPort.end() - 1)
            logger->error({name, I18N_PORT ":", std::to_string(port), I18N_SYSTEM_PORT_CHECK_1});
    }
}
void SysBase::adiCheck(const int port, const std::string name)
{
    for (auto it = _adiPort.begin(); it != _adiPort.end(); it++)
    {
        if (*it == port)
        {
            _adiPort.erase(it);
            break;
        }
        if (it == _adiPort.end() - 1)
            logger->error({name, I18N_PORT ":", std::to_string(port), I18N_SYSTEM_PORT_CHECK_1});
    }
}
void SysBase::adiCheck(const std::pair<int, int> port, const std::string name)
{
    int count = 0;
    if (port.first % 2 != 0)
        for (auto it = _adiPort.begin(); it != _adiPort.end(); it++)
        {
            if (*it == port.first || *it == port.second)
            {
                _adiPort.erase(it);
                count++;
                if (count == 2)
                    break;
            }
            if (it == _adiPort.end() - 1)
                logger->error({name, I18N_PORT ":", std::to_string(port.first), " ", std::to_string(port.second), I18N_SYSTEM_PORT_CHECK_1});
        }
    else
        logger->error({name, I18N_PORT ":", std::to_string(port.first), " ", std::to_string(port.second), I18N_SYSTEM_PORT_CHECK_2});
}
/**
    *增加部件名字 
    * @param str 部件的名字
    */
void SysBase::addObj(Obj *generic)
{
    obj.push_back(generic);
}
/**
     *获取当前机器人部件总数 
     * @return size_t 部件总数
     */
size_t SysBase::getObjNums()
{
    return obj.size();
}
/**
     *停止所有部件运作
     */
void SysBase::stopAllObj()
{
    for (auto &it : obj)
        it->stop();
}
void SysBase::print(const json &pragma, std::string_view ignore)
{
    for (auto &it : pragma.items())
        if (it.key() != ignore)
            for (auto &it1 : it.value().items())
            {
                std::cout << it1.key() << " ";
                for (auto &it2 : it1.value().items())
                    std::cout << it2.key() << ":" << it2.value() << " ";
                std::cout << std::endl;
            }
}
//递归打印
void SysBase::recursionPrint(const json &pragma, std::string_view ignore)
{
    for (auto &[key, val] : pragma.items())
    {
        if (key != ignore)
        {
            if (val.is_structured())
            {
                std::cout << "\n"
                          << key << ": "; //这里可以右移
                recursionPrint(val, ignore);
            }
            else
            {
                std::cout << key << ":" << val << " ";
            }
        }
    }
    return;
}

} // namespace ncrapi
