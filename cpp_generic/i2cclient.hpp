#ifndef I2CCLIENT_HPP_
#define I2CCLIENT_HPP_


/**
 * @class I2CClient
 * @brief Implements an I2C client
 */

class I2CClient
{
    int m_port;
    int m_id;

public:
    I2CClient(int port, int id);

    ~I2CClient();

    uint16_t getValue() const;
};



#endif
