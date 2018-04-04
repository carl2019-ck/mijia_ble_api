/**
 ****************************************************************************************
 *
 * @file mijia_task.h
 *
 * @brief Custom Service profile task header file.
 *
 * Copyright (C) 2017 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information
 * of Dialog Semiconductor. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */

#ifndef __MIJIA_TASK_PRF_H
#define __MIJIA_TASK_PRF_H

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#if (BLE_MIJIA_SERVER)

#include <stdint.h>
#include "ke_task.h"
#include "prf_types.h"
#include "compiler.h"        // compiler definition
#include "att.h"
#include "attm_db_128.h"
#include "mijia.h"
#include "mible_type.h"


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/// Possible states of the CUSTOMS task
enum mijia_state
{
    /// Idle state
    MIJIA_IDLE,
    /// Busy state
    MIJIA_BUSY,
    /// Number of defined states.
    MIJIA_STATE_MAX,
};

/// Messages for MIJIA
enum
{
    /// Add a CUSTOMS instance into the database
    MIJIA_CREATE_DB_REQ = KE_FIRST_MSG(TASK_ID_MIJIA),
    /// Inform APP of database creation status
    MIJIA_CREATE_DB_CFM,
    /// Start the Custom Service Task - at connection
    MIJIA_ENABLE_REQ,
    /// Indicate that the characteristic value has been written
    MIJIA_VAL_WRITE_IND,
    MIJIA_VAL_READ_IND,
    /// Inform the application that the profile service role task has been disabled after a disconnection
    MIJIA_DISABLE_IND,
    /// enable indication
    MIJIA_ENABLE_IND_NTF_REQ,
    ///Send indication to peer master
    MIJIA_SEND_INDICATION_REQ,
    ///Inform the handling result of indication result
    MIJIA_SEND_INDICATION_CFM,
    
    MIJIA_SEND_DATA_TO_MASTER,
		///Send notifcation to peer master
		MIJIA_SEND_NOTIFCATION_REQ,
    /// Profile error report
    MIJIA_ERROR_IND,


		//application msg & timer
		APP_MSG_CUS0,
		APP_MSG_CUS1=APP_MSG_CUS0+1,
		APP_MSG_CUS2=APP_MSG_CUS0+2,
		APP_MSG_CUS3=APP_MSG_CUS0+3,
		APP_MSG_CUS4=APP_MSG_CUS0+4,
		APP_MSG_CUS5=APP_MSG_CUS0+5,
		APP_MSG_CUS6=APP_MSG_CUS0+6,
		APP_MSG_CUS7=APP_MSG_CUS0+7,
		APP_MSG_CUS8=APP_MSG_CUS0+8,
		APP_MSG_CUS9=APP_MSG_CUS0+9,
		APP_MSG_CUS10=APP_MSG_CUS0+10,
		APP_MSG_SKY_LAST_MES=APP_MSG_CUS10,

		APP_CREATE_CUS_TIMER,
	  APP_CANCEL_CUS_TIMER,
	  APP_MODIFY_CUS_TIMER,

		APP_TIMER_CUS_MES0,
    APP_TIMER_CUS_MES1=APP_TIMER_CUS_MES0+1,
    APP_TIMER_CUS_MES2=APP_TIMER_CUS_MES0+2,
    APP_TIMER_CUS_MES3=APP_TIMER_CUS_MES0+3,
    APP_TIMER_CUS_MES4=APP_TIMER_CUS_MES0+4,
    APP_TIMER_CUS_MES5=APP_TIMER_CUS_MES0+5,
    APP_TIMER_CUS_MES6=APP_TIMER_CUS_MES0+6,
    APP_TIMER_CUS_MES7=APP_TIMER_CUS_MES0+7,
    APP_TIMER_CUS_MES8=APP_TIMER_CUS_MES0+8,
    APP_TIMER_CUS_MES9=APP_TIMER_CUS_MES0+9,
    APP_TIMER_CUS_MES10=APP_TIMER_CUS_MES0+10,
    APP_TIMER_CUS_MES11=APP_TIMER_CUS_MES0+11,
    APP_TIMER_CUS_MES12=APP_TIMER_CUS_MES0+12,
    APP_TIMER_CUS_MES13=APP_TIMER_CUS_MES0+13,
    APP_TIMER_CUS_MES14=APP_TIMER_CUS_MES0+14,
    APP_TIMER_CUS_MES15=APP_TIMER_CUS_MES0+15,
    APP_TIMER_CUS_MES16=APP_TIMER_CUS_MES0+16,
    APP_TIMER_CUS_LAST_MES=APP_TIMER_CUS_MES16,
};

/*
 * API MESSAGES STRUCTURES
 ****************************************************************************************
 */

/// Parameters for the database creation
struct mijia_db_cfg
{
    ///max number of casts1 service characteristics
    uint8_t max_nb_att;
    uint8_t *att_tbl;
    uint8_t *cfg_flag;

    ///Database configuration
    uint16_t features;
};

/// Parameters of the @ref MIJIA_CREATE_DB_CFM message
struct mijia_create_db_cfm
{
    ///Status
    uint8_t status;
};

/// Parameters of the @ref MIJIA_ENABLE_REQ message
struct mijia_enable_req
{
    /// Connection Handle
    uint16_t conhdl;
    /// Security level
    uint8_t sec_lvl;    
    /// MIJIA_IDX_IND_VAL property status
    uint8_t feature;
};

/// Parameters of the @ref MIJIA_DISABLE_IND message
struct mijia_disable_ind
{
    /// Connection Handle
    uint16_t conhdl;
};

/// Parameters of the @ref MIJIA_VAL_WRITE_IND massage
struct mijia_val_write_ind
{
		mible_gatts_evt_t evt;
    /// Connection handle
    uint16_t conhdl;
    /// data length
    uint16_t length;
		uint16_t value_handle;
    /// Value
    uint8_t value[BLE_MIJIA_MAX_DATA_LEN];
};

/// Parameters of the @ref MIJIA_VAL_READ_IND massage
struct mijia_val_read_ind
{
		mible_gatts_evt_t evt;
    /// Connection handle
    uint16_t conhdl;
    /// data length
    uint16_t length;
		uint16_t handle;
    /// Value
    uint8_t value[BLE_MIJIA_MAX_DATA_LEN];
};


/// Parameters of the @ref MIJIA_ENABLE_IND_NTF_REQ message
struct mijia_enable_indication_req
{
    /// Connection handle
    uint16_t conhdl;
		uint16_t value_handle;
    /// 0  FALSE   1  NTF  2 IND
    uint16_t isEnable;
    
};

/// Parameters of the @ref MIJIA_SEND_INDICATION_REQ message
struct mijia_indication_req
{
    /// Connection handle
    uint16_t conhdl;
		uint16_t value_handle;
    /// Indicated data length
    uint16_t length;
    /// Characteristic Value
    uint8_t value[BLE_MIJIA_MAX_DATA_LEN];
    
};

/// Parameters of the @ref MIJIA_SEND_NOTIFCATION_REQ message

struct mijia_notifcation_req
{
		uint8_t value_handle;
		/// Connection handle
    uint16_t conhdl;
    /// Indicated data length
    uint16_t length;
    /// Characteristic Value
    uint8_t value[BLE_MIJIA_MAX_DATA_LEN];
};

/// Parameters of the @ref MIJIA_SEND_INDICATION_CFM message
struct mijia_indication_cfm
{
    /// Status
    uint8_t status;
};

struct mijia_send_data_req
{
    uint32_t dataLen;
    uint8_t* pDataBuf;
};


/**
 ****************************************************************************************
 * @brief Initialize Client Characteristic Configuration fields.
 * @details Function initializes all CCC fields to default value.
 * @param[in] att_db         Id of the message received.
 * @param[in] max_nb_att     Pointer to the parameters of the message.
 ****************************************************************************************
 */
void mijia_init_ccc_values(const struct attm_desc_128 *att_db, int max_nb_att);

/**
 ****************************************************************************************
 * @brief Set per connection CCC value for attribute
 * @details Function sets CCC for specified connection.
 * @param[in] conidx         Connection index.
 * @param[in] att_idx        Attribute index.
 * @param[in] ccc            Value of ccc.
 ****************************************************************************************
 */
void mijia_set_ccc_value(uint8_t conidx, uint8_t att_idx, uint16_t ccc);


bool ble_mijia_gatts_value_get(uint16_t srv_handle, uint16_t value_handle,
    uint8_t* p_value, uint8_t *p_len);

mible_status_t mijia_gatts_value_set_direct(uint16_t srv_handle,
	uint16_t value_handle, uint8_t offset,uint8_t* p_value, uint8_t len);


void ble_mijia_gatts_notify_or_indicate(uint16_t conn_handle, uint16_t srv_handle,
    uint16_t char_value_handle, uint8_t offset, uint8_t* p_value,
    uint8_t len, uint8_t type);

mible_status_t mijia_send_notifcation_req_handler_direct(ke_msg_id_t const msgid,
																		struct mijia_notifcation_req const *param,
																		ke_task_id_t const dest_id,
																		ke_task_id_t const src_id);

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler mijia_state_handler[MIJIA_STATE_MAX];
extern const struct ke_state_handler mijia_default_handler;

#endif // BLE_MIJIA_SERVER
#endif // __MIJIA_TASK_PRF_H
