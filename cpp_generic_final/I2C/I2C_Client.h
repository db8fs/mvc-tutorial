#ifndef I2CCLIENT_HPP_
#define I2CCLIENT_HPP_


/**
 * @brief Implements an I2C client
 */

class I2C_Client
{
    int m_port;
    int m_id;

public:
    //! construction with I2C port and I2C client id
    I2C_Client(int port, int id);

    //! destruction
    ~I2C_Client();

    //! gets a 16-bit value
    uint16_t getValue() const;
};



#endif
