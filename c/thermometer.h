
#ifndef THERMOMETER_H_
#define THERMOMETER_H_

/**
 * @file thermometer.h
 * @brief Implements the MVC pattern for a sample thermometer using ANSI-C
 */


/**
 * @struct thermo_controller
 * @brief opaque handle for a thermometer
 * @remark implementation transparent in object file
 */

struct thermo_controller;


/**
 * @enum   thermo_type
 * @brief  'Polymorphic' type of the MVP data model
 * @detail Selects the hardware backend for the used thermometer.
 */

enum thermo_type
{
    TYPE_NONE=0,
    TYPE_DS1621=1
};


/**
 * @typedef thermo_view
 * @brief   MVP View for thermometer data model
 */

typedef
void (*thermo_view) ( const struct thermo_controller* const );


/**
 * @enum  thermo_unit
 * @brief Part of the MVP Data Model @sa{thermo_model}
 */

enum thermo_unit
{
    UNIT_CELSIUS=0,
    UNIT_FAHRENHEIT
};


/**
 * @fn thermometer_init
 * @brief initializes a thermometer
 */

struct thermo_controller* thermometer_init_i2c( int port, int id);


/**
 * @fn thermometer_cleanup
 * @brief deinitializes the ressource of a thermocontroller
 */

void thermometer_cleanup_i2c( struct thermo_controller* );


/**
 * @fn th_controller_update
 * @brief triggers updates of the thermometer
 */

void thermometer_update( struct thermo_controller* );


/**
 * @fn  thermometer_set_model
 * @brief selects the data model for the given controller
 * @param thermo_controller  the thermometer to use
 * @param thermo_type the type of the thermometer to control
 * @return the MVP data model handle
 */

void thermometer_set_model( struct thermo_controller*, enum thermo_type );


/**
 * @fn th_controller_set_unit
 * @brief selects the displaying unit
 */

void thermometer_set_unit( struct thermo_controller*, enum thermo_unit );


/**
 * @fn th_controller_add_view
 * @brief adds a view to a given thermometer
 */

void thermometer_add_view( struct thermo_controller*, thermo_view );


/**
 * @fn th_controller_del_view
 * @brief removes a view from a given thermometer
 */

void thermometer_del_view( struct thermo_controller*, thermo_view );


/**
 * @fn th_get_temperature
 * @brief gets the thermometer's temperature
 */

float thermometer_get_temperature( const struct thermo_controller* );


/**
 * @fn th_getunit
 * @brief gets the unit (@sa{enum thermo_unit})
 */

enum thermo_unit thermometer_get_unit( const struct thermo_controller* );


/**
 * @fn thermometer_get_type
 * @brief gets the type (@sa{enum thermo_type})
 */

enum thermo_type thermometer_get_type( const struct thermo_controller* );


#endif // THERMOMETER_H_
