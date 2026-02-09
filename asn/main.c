#include <stdio.h>
#include <string.h>
#include <teste.h>
#include "rcwrapper.h"
//#include "kpmwrapper.h"

//int get_data(char *rawdata, char *data);
void teste();

char data_ok[12000];

int main(){
    printf("INIT TESTE ASN\n");
    char n[]={0,3,4};
    //encode_rc_action_Definition(n,2);
    //encode_rc_eventrigger(n,2);
    //encode_rc_eventrigger(n,5);
    //e2sm_decode_ric_indication_message(n, 3);
    
    //teste();

    E2SM_RC_IndicationHeader_t *indHdr =  e2sm_decode_rc_ric_indication_header(RICIndicationHeader,strlen(RICIndicationHeader));
    printf("Insert Style %d\n",indHdr->ric_indicationHeader_formats.choice.indicationHeader_Format2->ric_InsertStyle_Type);
    //E2SM_RC_IndicationMessage_t *indMsg = e2sm_decode_rc_ric_indication_message(RICIndicationMessage, strlen(RICIndicationMessage));

    printf("\n==================================================\n");
    printf("\n=======\tRIC CONTROL REQUEST\t========\n");
    printf("\n==================================================\n");

    /*  CONTROL   HEADER    */
    //e2sm_encode_ric_control_header(void *buffer, size_t buf_size,struct uEID *in,long f1AP[],size_t f1AP_len,long e1AP[],size_t e1Ap_len,long ricControlStyleType, long ricControlActionID, void *ranParameterValue, size_t ranParameterValue_size);
   
    size_t data_len;
    //int resul = e2sm_encode_ric_control_header(data_ok, &data_len);
    //for(int i=0; i < resul; i++)
    //    printf("%d|",data_ok[i]);
    //printf("\n");

    /*  CONTROL   MESSAGE    */
    //extern ssize_t e2sm_encode_ric_control_message(void *buffer, size_t buf_size, long targetPrimaryCell, long targetCell, long nrOrEUtraCell, long nrCGIOrECGI, void *ranParameterValue,  size_t  ranParameterValue_size);
    e2sm_encode_ric_control_message(data_ok, &data_len);

    return 0;
}
/*
void teste()
{
    E2SM_KPM_IndicationMessage_t *indMsg_du = 0;
    
    //indMsg_du = e2sm_decode_ric_indication_message(_data_CU, strlen(_data_CU));
    //printf("\n ******************************************************* \n");
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    //printf("\n ================================================ \n");

    //indMsg_du = e2sm_decode_ric_indication_message(_data_OK, strlen(_data_OK));
    //printf("\n ******************************************************* \n");
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    //printf("\n ================================================ \n");

    printf("\n ******************************************************* \n");
    get_data(data1,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data2,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data3,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data4,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data5,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data6,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data7,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data8,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data9,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data10,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data11,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data12,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

        printf("\n ******************************************************* \n");
    get_data(data13,data_ok);
    indMsg_du =  e2sm_decode_ric_indication_message(data_ok, strlen(data_ok));
    //xer_fprint(stdout, &asn_DEF_E2SM_KPM_IndicationMessage, indMsg_du);
    printf("\n ================================================ \n");

    //get_data(data2,data_ok);
    //printf("2- DATA OK %s\n",data_ok);
}

int get_data(char *rawdata, char *data)
{
    char compare[22]="003020000001400000081";
    char ref[22];
    int comp = 0;
    int i=0;
    for(i; i< 250-strlen(compare); i++)
    {
        strncpy(ref,rawdata+i,strlen(compare));
        comp = strcmp(ref,compare);
        //printf("%d-> com %d [%s = %s]\n",i,comp,ref,compare);
        if(comp == 0)
            break;
        
    }

    if (comp == 0)
    {
        memcpy(data,rawdata,i);
        data[1] = 4;
        strcat(data,"40270f");
        printf("%d data ok [%s] FIM\n",i,data);
    }else{
        memcpy(data,rawdata,strlen(rawdata));
    }
    return comp;
}

*/