#ifndef	_RCWRAPPER_H_
#define	_RCWRAPPER_H_

#include "BOOLEAN.h"
#include "NativeReal.h"
#include "REAL.h"
#include "OCTET_STRING.h"
#include "E2SM-RC-ControlHeader-Format1.h"
#include "E2SM-RC-ControlHeader.h"
#include "E2SM-RC-ControlMessage-Format1.h"
#include "E2SM-RC-ControlMessage.h"
#include "E2SM-RC-RANFunctionDefinition.h"
#include "INTEGER.h"
#include "NativeInteger.h"
#include "OPEN_TYPE.h"
#include "PrintableString.h"
#include "RANParameter-ID.h"
#include "RANParameter-LIST.h"
#include "RANParameter-Name.h"
#include "RANParameter-STRUCTURE.h"
#include "RANParameter-Value.h"
#include "RANParameter-ValueType.h"
#include "RANfunction-Name.h"
#include "RIC-ControlAction-ID.h"
#include "RIC-ControlAction-Name.h"
#include "RIC-Format-Type.h"
#include "RIC-Style-Name.h"
#include "RIC-Style-Type.h"
#include "RANParameter-ValueType-Choice-ElementFalse.h"
#include "RANParameter-ValueType-Choice-ElementTrue.h"
#include "RANParameter-ValueType-Choice-Structure.h"
#include "RANParameter-ValueType-Choice-List.h"
#include "UEID.h"
#include "UEID-GNB.h"
#include "UEID-GNB-CU-F1AP-ID-List.h"
#include "UEID-GNB-CU-CP-E1AP-ID-List.h"
#include "UEID-GNB-CU-CP-F1AP-ID-Item.h"
#include "UEID-GNB-CU-CP-E1AP-ID-Item.h"
#include "E2SM-RC-ControlMessage-Format1-Item.h"
#include "RANParameter-STRUCTURE-Item.h"
#include "E2SM-RC-ControlOutcome.h"
#include "E2SM-RC-ControlOutcome-Format1.h"
#include "E2SM-RC-ControlOutcome-Format1-Item.h"
#include "NR-CGI.h"

#include "RANFunctionDefinition-EventTrigger.h"
#include "RANFunctionDefinition-EventTrigger-Style-Item.h"
#include "RANFunctionDefinition-EventTrigger-CallProcess-Item.h"
#include "RANFunctionDefinition-EventTrigger-Breakpoint-Item.h"

#include "E2SM-RC-ActionDefinition.h"
#include "E2SM-RC-ActionDefinition-Format3.h"
#include "E2SM-RC-ActionDefinition-Format3-Item.h"
#include "RANParameter-Definition-Choice.h"
#include "RANParameter-Definition-Choice-LIST.h"
#include "RANParameter-Definition-Choice-LIST-Item.h"

#include "RANFunctionDefinition-Insert.h"
#include "RANFunctionDefinition-Insert-Item.h"
#include "RANFunctionDefinition-Insert-Indication-Item.h"

#include "RANFunctionDefinition-Control.h"
#include "RANFunctionDefinition-Control-Item.h"
#include "RANFunctionDefinition-Control-Action-Item.h"

#include "E2SM-RC-EventTrigger.h"
#include "E2SM-RC-EventTrigger-Format2.h"
#include "RIC-CallProcessType-ID.h"
#include "RIC-CallProcessBreakpoint-ID.h"

#include "E2SM-RC-EventTrigger-Format5.h"
#include "EventTrigger-UEevent-Info.h"
#include "EventTrigger-UEevent-Info-Item.h"
#include "EventTrigger-UE-Info.h"
#include "EventTrigger-UE-Info-Item.h"
#include "EventTrigger-UE-Info-Item-Choice-Individual.h"
#include "EventTrigger-UE-Info-Item-Choice-Group.h"
#include "EventTrigger-Cell-Info.h"
#include "EventTrigger-Cell-Info-Item.h"
#include "EventTrigger-Cell-Info-Item-Choice-Individual.h"
#include "EventTrigger-Cell-Info-Item-Choice-Group.h"
#include "RIC-EventTrigger-Cell-ID.h"

#include "PLMNIdentity.h"
#include "EUTRACellIdentity.h"

#include "RANParameter-Definition.h"
#include "InsertIndication-RANParameter-Item.h"
#include "RANParameter-ID.h"
#include "RANParameter-Name.h"

typedef struct encode_rc_act_Def_result{
	int * array;
	int length;
} encode_rc_act_Def_result_t;

long    F1AP_id[1];
long    E1AP_id[1];
struct uEID {
    long    amf_UE_NGAP_Id;
    //size_t  amf_UE_NGAP_Id_size;
    const char* pLMNIdentity;
    size_t  pLMNIdentity_size;
    const char* aMFRegionID;
    size_t  aMFRegionID_size;
    const char* aMFSetID;
    size_t  aMFSetID_size;
    const char* aMFPointer;
    size_t  aMFPointer_size;
};


extern ssize_t e2sm_encode_ric_control_header(void *buffer, size_t buf_size,struct uEID *in,long f1AP[],size_t f1AP_len,long e1AP[],size_t e1Ap_len,long ricControlStyleType, long ricControlActionID, void *ranParameterValue, size_t ranParameterValue_size);

extern ssize_t e2sm_encode_ric_control_header_qos(void *buffer, size_t buf_size,struct uEID *in,long f1AP[],size_t f1AP_len,long e1AP[],size_t e1Ap_len,long ricControlStyleType, long ricControlActionID, void *ranParameterValue, size_t ranParameterValue_size, long ricControlDecision);

extern ssize_t e2sm_encode_ric_control_message(void *buffer, size_t buf_size, long targetPrimaryCell, long targetCell, long nrOrEUtraCell, long nrCGIOrECGI, void *ranParameterValue,  size_t  ranParameterValue_size);

extern ssize_t e2sm_encode_ric_control_message_qos( void *buffer, size_t buf_size, long drb_id, long qos_flow_id, long five_qi, long priority_level);

struct encode_rc_act_Def_result encode_rc_action_Definition(const char *_hex_values, int determine);
int e2sm_encode_ric_insert_definition_format3(unsigned char *buf, size_t *buf_size, char **id_tmp , size_t measIdcount, long ric_style_type,  unsigned char  *p, unsigned char *nR);

struct encode_rc_act_Def_result encode_rc_eventrigger(const char *_hex_values, int determine);
int e2sm_encode_ric_encode_rc_eventrigger_format2(unsigned char *buf, size_t *buf_size);
int e2sm_encode_ric_encode_rc_eventrigger_format5(unsigned char *buf, size_t *buf_size);

extern E2SM_RC_ControlOutcome_t* e2sm_decode_ric_call_process_outcome(void *buffer, size_t buf_size);
extern void e2sm_free_ric_call_process_outcome(E2SM_RC_ControlOutcome_t* controlOutcome) ;
extern ssize_t e2sm_encode_nrcgi(NR_CGI_t *nr_cgi, void* ranParameterValue, size_t ranParameterValue_size,
				long lNRCellId,uint8_t* buffer, size_t buf_size);

#endif /* _WRAPPER_H_ */
