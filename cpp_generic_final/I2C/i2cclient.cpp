#include <stdint.h>
#include "i2cclient.hpp"

extern void i2c_read_uint16( int, int, uint16_t* );

I2C_Client::I2C_Client(int port, int id)
    : m_port(port), m_id(id)
{}


I2C_Client::~I2C_Client()
{}

uint16_t I2C_Client::getValue() const
{
    uint16_t val(0);
    i2c_read_uint16( m_port, m_id, &val );
    return val;
}
