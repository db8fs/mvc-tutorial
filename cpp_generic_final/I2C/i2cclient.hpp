#ifndef I2CCLIENT_HPP_
#define I2CCLIENT_HPP_


/**
 * @class I2CClient
 * @brief Implements an I2C client
 */

class I2C_Client
{
    int m_port;
    int m_id;

public:
    I2C_Client(int port, int id);

    ~I2C_Client();

    uint16_t getValue() const;
};



#endif
