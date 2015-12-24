#include "thermometer.h"
#include <stdlib.h>

// sample I2C API to use for acquiring data
extern void i2c_read_float( int, int, float* );


#ifndef THERMOMETER_MAX_VIEWS
# define THERMOMETER_MAX_VIEWS 16
#endif


/**
 * @typedef thermo_model
 * @brief MVP Data Model for thermometer
 */

struct thermo_model
{
    float temperature;
    enum thermo_unit unit;
    enum thermo_type type;
    thermo_view views[ THERMOMETER_MAX_VIEWS ];
};



/**
 * @typedef thermo_controller
 * @brief MVP Controller for thermometers
 * @remark Holds everything needed for data acquisition (e.g. I2C port + identifier), but no parsed data!!!
 */

struct thermo_controller
{
    struct thermo_model* model; // the data model of the sensor
    int port;  // the I2C port to use
    int id;    // the I2C id of the sensor
};


/**
 * @fn notify_views
 * @brief notifies all views of the given data model
 */

static void notify_views( struct thermo_controller* controller )
{
    struct thermo_model* model=controller->model;

    int i;
    for(i=0; i<THERMOMETER_MAX_VIEWS; ++i )
    {
        thermo_view view=model->views[i];

        if( view != NULL )
        {
            view( controller );
        }
    }
}


void thermometer_add_view( struct thermo_controller* controller, thermo_view fn )
{
    if( NULL != controller && NULL != fn )
    {
        struct thermo_model* model=controller->model;

        if( NULL != model )
        {
            int i;
            for( i=0; i < THERMOMETER_MAX_VIEWS; ++i )
            {
                if( model->views[i] == NULL )
                {
                    model->views[i] = fn;
                    fn( controller );
                    return;
                }
            }
        }
    }
}

void thermometer_del_view( struct thermo_controller* controller, thermo_view fn )
{
    if( NULL != controller && NULL != fn )
    {
        struct thermo_model* model=controller->model;

        if( NULL != model )
        {
            int i;
            for( i=0; i< THERMOMETER_MAX_VIEWS; ++i )
            {
                if( model->views[i] == fn )
                {
                    model->views[i] = NULL;
                }
            }
        }
    }
}

struct thermo_controller* thermometer_init_i2c( int port, int id)
{
    return malloc( sizeof(struct thermo_controller) );
}

void thermometer_cleanup_i2c( struct thermo_controller* th)
{
    free(th);
}




/**
 * @fn thermometer_set_model
 * @brief selects the thermometer model
 */

void thermometer_set_model( struct thermo_controller* controller, enum thermo_type type )
{
    if( controller != NULL )
    {
        struct thermo_model* model = controller->model;

        if( NULL != model )
        {
            if( model->type != type )
            {
                model->type = type;
            }
        }
        else
        {
            controller->model = malloc( sizeof(struct thermo_model) );
            controller->model->type = type;
            controller->model->unit = UNIT_CELSIUS;
            controller->model->temperature = 0.f;
        }

        notify_views( controller );
    }
}



void thermometer_update( struct thermo_controller* controller )
{
    if( NULL != controller )
    {
        struct thermo_model* model=controller->model;

        switch( model->type )
        {
        case TYPE_DS1621:
            i2c_read_float( controller->port, controller->id, &model->temperature );
            break;

        case TYPE_NONE:
        default:
            break;
        }
    }
}


void thermometer_set_unit( struct thermo_controller* controller, enum thermo_unit unit )
{
    if( NULL != controller )
    {
        struct thermo_model* model=controller->model;

        if( NULL != model )
        {
            model->unit = unit;
        }
    }
}


enum thermo_unit thermometer_get_unit( const struct thermo_controller* controller )
{
    if( NULL != controller )
    {
        if( NULL != controller->model )
        {
            return controller->model->type;
        }
    }

    return UNIT_CELSIUS;
}


enum thermo_type thermometer_get_type( const struct thermo_controller* controller )
{
    if( NULL != controller )
    {
        if( NULL != controller->model )
        {
            return controller->model->type;
        }
    }

    return TYPE_NONE;
}

float thermometer_get_temperature( const struct thermo_controller* controller )
{
    if( NULL != controller )
    {
        if( NULL != controller->model )
        {
            return controller->model->temperature;
        }
    }

    return 0.f;
}
