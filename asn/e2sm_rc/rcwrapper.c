#include <errno.h>
#include "rcwrapper.h"
#include "OCTET_STRING.h"



struct encode_rc_act_Def_result encode_rc_eventrigger(const char *_hex_values, int determine)
{
        encode_rc_act_Def_result_t res;	

        int BUFFER_SIZE=10240;

        /*      FORMAT 2        */        
        /*
        unsigned char bufFormat2[BUFFER_SIZE];
        size_t buf_sizeFormat2 = BUFFER_SIZE;

        int encodedLengthFormat2 = e2sm_encode_ric_encode_rc_eventrigger_format2(&bufFormat2[0], &buf_sizeFormat2);

        printf("\n");
	int rcarrayFormat2[encodedLengthFormat2];
        for(int i=0;i<encodedLengthFormat2;i++){
                        printf("%d ",(int)bufFormat2[i]);
			rcarrayFormat2[i]=(int)bufFormat2[i];
        }
        printf("\n");
        */

        /*      FORMAT 5        */
        
        unsigned char bufFormat5[BUFFER_SIZE];
        size_t buf_sizeFormat5 = BUFFER_SIZE;

        int encodedLengthFormat5 = e2sm_encode_ric_encode_rc_eventrigger_format5(&bufFormat5[0], &buf_sizeFormat5);

        printf("\n");
	int rcarrayFormat5[encodedLengthFormat5];
        for(int i=0;i<encodedLengthFormat5;i++){
                        printf("%d ",(int)bufFormat5[i]);
			rcarrayFormat5[i]=(int)bufFormat5[i];
        }
        printf("\n");
        

	switch(determine){
		case 1:
			//res.array=rcarrayFormat3;
			//res.length=encodedLengthFormat3; //-8;//removing hardcoded plmn and cellid
			return res;
		case 2:
                        //res.array = rcarrayFormat2;
			//res.length= encodedLengthFormat2;//-8;//removing hardcoded plmn and cellid
			return res;
		case 3:
			//res.array=arrayFormat3ById;
			//res.length=encodedLengthFormat3ById;
			//return res;
		case 4:
			//res.array=arrayFormat3ByName;
			//res.length=encodedLengthFormat3ByName;
			//return res;
                case 5:
			res.array=rcarrayFormat5;
			res.length=encodedLengthFormat5;
			return res;
			break;

	}

        return res;
}

int e2sm_encode_ric_encode_rc_eventrigger_format2(unsigned char *buf, size_t *buf_size)
{
        E2SM_RC_EventTrigger_t* evenTrigger = (E2SM_RC_EventTrigger_t*)calloc(1,sizeof(E2SM_RC_EventTrigger_t));
         if (!evenTrigger ) {
                fprintf(stderr, "alloc RIC Event Trtigger format 2 failed\n");
                return -1;
        }

        evenTrigger->ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format2;

        evenTrigger->ric_eventTrigger_formats.choice.eventTrigger_Format2 = (E2SM_RC_EventTrigger_Format2_t*)calloc(1,sizeof(E2SM_RC_EventTrigger_Format2_t));
        evenTrigger->ric_eventTrigger_formats.choice.eventTrigger_Format2->ric_callProcessBreakpoint_ID = 1; 
        evenTrigger->ric_eventTrigger_formats.choice.eventTrigger_Format2->ric_callProcessType_ID = 1;
                
        char errbuf[128];
        size_t errbuf_len = 128;

        int ret_constr = asn_check_constraints(&asn_DEF_E2SM_RC_EventTrigger, (void *)evenTrigger, errbuf, &errbuf_len);
        if(ret_constr){
                fprintf(stderr,"Constraints failed for encoding subscription request, %s", strerror(errno));
                return -1;
        }
        
        printf("Estructura RANFunctionDefiniton\n");
        asn_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, evenTrigger);
        asn_enc_rval_t encode_result = asn_encode_to_buffer(0,ATS_ALIGNED_CANONICAL_PER,&asn_DEF_E2SM_RC_EventTrigger,evenTrigger, buf, *buf_size);        
        
        if (encode_result.encoded == -1) {
                fprintf(stderr, "Cannot encode %s: %s in line %d, file %s\n", encode_result.failed_type->name, strerror(errno),  __LINE__, __FILE__);
                return -1;
        }
        else {
                fprintf(stderr, "successfully\n");
                return encode_result.encoded;
        }
        
}

int e2sm_encode_ric_encode_rc_eventrigger_format5(unsigned char *buf, size_t *buf_size)
{
        E2SM_RC_EventTrigger_t* evenTrigger = (E2SM_RC_EventTrigger_t*)calloc(1,sizeof(E2SM_RC_EventTrigger_t));
         if (!evenTrigger ) {
                fprintf(stderr, "alloc RIC Event Trtigger format 2 failed\n");
                return -1;
        }
        
        EventTrigger_Cell_Info_t **infoCell = (EventTrigger_Cell_Info_t**)calloc(1,sizeof(EventTrigger_Cell_Info_t*));
        //EventTrigger_UE_Info_t **infoUe = (EventTrigger_UE_Info_t**)calloc(1,sizeof(EventTrigger_UE_Info_t*));

        evenTrigger->ric_eventTrigger_formats.present = E2SM_RC_EventTrigger__ric_eventTrigger_formats_PR_eventTrigger_Format5;
        evenTrigger->ric_eventTrigger_formats.choice.eventTrigger_Format5 = (E2SM_RC_EventTrigger_Format5_t*)calloc(1,sizeof(E2SM_RC_EventTrigger_Format5_t));
        evenTrigger->ric_eventTrigger_formats.choice.eventTrigger_Format5->onDemand = 0;

                //get plmn id during run time of kpimon
        //unsigned char p[] = {0x00, 0xF1, 0x10};
        unsigned char p[] = {0x00, 0xF1, 0x10};

        //get nr cell id for 5g cell or eutra cell id for 4g cell
        //unsigned char nR []= {0x12, 0x34, 0x56, 0x00, 0x10};
        //unsigned char nR []= {0x00, 0x00, 0x01, 0x00, 0x10};

        //      Radisys 1.7.10.127    /
        unsigned char nR []= {0x00, 0x00, 0x00, 0x00, 0x10};

        NR_CGI_t *NRG = (NR_CGI_t*)calloc(1,sizeof(NR_CGI_t));

        PLMNIdentity_t *PLMN = (PLMNIdentity_t *)calloc(1,sizeof(PLMNIdentity_t));
        PLMN->buf = (uint8_t*)calloc(3,sizeof(uint8_t));
        memcpy(PLMN->buf,p,3);
        PLMN->size = 3;

        NRCellIdentity_t *NRC = (NRCellIdentity_t*)calloc(1,sizeof(NRCellIdentity_t));
        NRC->buf = (uint8_t*)calloc(5,sizeof(uint8_t));
        memcpy(NRC->buf,nR,5);
        NRC->size = 5;
        NRC->bits_unused = 4;

        NRG->nRCellIdentity = *NRC;
        NRG->pLMNIdentity = *PLMN;

        CGI_t *globalCell = (CGI_t*)calloc(1,sizeof(CGI_t));

        globalCell->choice.nR_CGI = NRG;
        globalCell->present = CGI_PR_nR_CGI;

        EventTrigger_Cell_Info_Item_t *cellInfoItem = (EventTrigger_Cell_Info_Item_t*)calloc(1,sizeof(EventTrigger_Cell_Info_Item_t*));
        cellInfoItem->cellType.present = EventTrigger_Cell_Info_Item__cellType_PR_cellType_Choice_Individual;
        cellInfoItem->logicalOR = 0;
        cellInfoItem->cellType.choice.cellType_Choice_Individual =  (EventTrigger_Cell_Info_Item_Choice_Individual_t*)calloc(1,sizeof(EventTrigger_Cell_Info_Item_Choice_Individual_t));
        cellInfoItem->cellType.choice.cellType_Choice_Individual->cellGlobalID = *globalCell;
        cellInfoItem->eventTriggerCellID = 1;

        int index = 0;
        while(index < 1)
        {
                infoCell[index] = (EventTrigger_Cell_Info_t*)calloc(1,sizeof(EventTrigger_Cell_Info_t));
                int resutl1 = ASN_SEQUENCE_ADD(&infoCell[index]->cellInfo_List,cellInfoItem);
                if(resutl1){
                      fprintf(stderr,"Constraints failed for encoding subscription request, %s", strerror(errno));
                      return -1;
                }
                printf("\n1- Sequence %d\n",infoCell[index]->cellInfo_List.list.count);
            index++;
        }
        
        evenTrigger->ric_eventTrigger_formats.choice.eventTrigger_Format5->associatedCellInfo = *infoCell;
        printf("Estructura RANFunctionDefiniton\n");
        asn_fprint(stdout, &asn_DEF_E2SM_RC_EventTrigger, evenTrigger);
        
        asn_enc_rval_t encode_result = asn_encode_to_buffer(0,ATS_ALIGNED_CANONICAL_PER,&asn_DEF_E2SM_RC_EventTrigger,evenTrigger, buf, *buf_size);        
        
        if (encode_result.encoded == -1) {
                fprintf(stderr, "Cannot encode %s: %s in line %d, file %s\n", encode_result.failed_type->name, strerror(errno),  __LINE__, __FILE__);
                return -1;
        }
        else {
                fprintf(stderr, "successfully\n");
                return encode_result.encoded;
        }
        
        return -1;
}

//determine 
//1 for format1 by id, 2 for format1 by name , 3 for format3 by id, 4 for format3 by name
//struct encode_act_Def_result encode_action_Definition(const char *hex_values, int determine){
struct encode_rc_act_Def_result encode_rc_action_Definition(const char *_hex_values, int determine){
 	
        // CU
        // char hex_values[] = "7805804f52414e2d4532534d2d5243000018312e332e362e312e342e312e35333134382e312e312e322e3300805243202001020b0043616c6c2050726f6365737320427265616b706f696e74010200010106004d657373616765204576656e74010100000000050a805044552053657373696f6e204d616e6167656d656e7400024000000c805044552053657373696f6e205265736f7572636520536574757000029075320e004c697374206f6620516f5320466c6f777320746f206265207365747570009075330d00516f5320666c6f772073657475702072657175657374206974656d009075350380516f5320666c6f770040000110005044552053657373696f6e205265736f75726365204d6f64696669636174696f6e000290791a10804c697374206f6620516f5320466c6f777320746f20616464206f72206d6f646966790090791b1100516f5320666c6f7720616464206f72206d6f646966792072657175657374206974656d0090791d0380516f5320666c6f77000000020d805044552053657373696f6e205265736f757263652052656c65617365028001020b0043616c6c2050726f6365737320427265616b706f696e740102010101010102000080000580445242204964656e746974790040010105804d65737361676520436f70790101010101010101000080020500525243204d65737361676500008001010d80526164696f2042656172657220436f6e74726f6c20526571756573740102010300004000030f00526164696f2061646d697373696f6e20636f6e74726f6c2072657175657374000080000580445242204964656e746974790001020105010102c001010980526164696f2042656172657220436f6e74726f6c00000000030b00526164696f2061646d697373696f6e20636f6e74726f6c0101010101010101600226ad1080484f2044657374696e6174696f6e20446973747269627574656420436f6e74726f6c00000000001680484f2044657374696e6174696f6e20446973747269627574656420436f6e74726f6c20496e737472756374696f6e0101010101010101";
        // DU
        //char hex_values[]="1805804F52414E2D4532534D2D5243000018312E332E362E312E342E312E35333134382E312E312E322E3300805243008001040D80526164696F2041636365737320436F6E74726F6C20526571756573740105010300004000020E804163636573732062617272696E6720636F6E74726F6C2072657175657374000080001100556E69666965642041636365737320436F6E74726F6C2042617272696E6720496E666F0001020105010100C001040980526164696F2061636365737320636F6E74726F6C00004000020A804163636573732062617272696E6720636F6E74726F6C000080001100556E69666965642041636365737320436F6E74726F6C2042617272696E6720496E666F000101010101010101";
        char hex_values[]="1805804f52414e2d4532534d2d5243000018312e332e362e312e342e312e35333134382e312e312e322e3300805243008001040d80526164696f2041636365737320436f6e74726f6c20526571756573740105010300004000020e804163636573732062617272696e6720636f6e74726f6c2072657175657374000080001100556e69666965642041636365737320436f6e74726f6c2042617272696e6720496e666f0001020105010100c001040980526164696f2061636365737320636f6e74726f6c00004000020a804163636573732062617272696e6720636f6e74726f6c000080001100556e69666965642041636365737320436f6e74726f6c2042617272696e6720496e666f000101010101010101";
        fprintf(stdout, "hex value %s length %ld\n",hex_values,strlen(hex_values));
        fprintf(stdout, "determine %d\n",determine);

	encode_rc_act_Def_result_t res;	
	int BUFFER_SIZE=10240;
        // Calculate the length of the hex string
        size_t hex_len = strlen(hex_values);

        // Allocate memory for a char array to store the hex values
        char *hex_buffer = (char *)malloc(hex_len / 2 + 1); // Each byte is represented by 2 characters, +1 for null terminator

        if (hex_buffer == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return res;
        }

        // Convert the hex string to binary data
        for (size_t i = 0; i < hex_len; i += 2) {
                char byte[3] = {hex_values[i], hex_values[i + 1], '\0'};
                hex_buffer[i / 2] = (char)strtol(byte, NULL, 16);
        }

        // Null-terminate the char array
        hex_buffer[hex_len / 2] = '\0';

        // Now hex_buffer contains the binary data corresponding to the hex values

        // Print the result
        fprintf(stderr,"Hex values as a string: %s\n", hex_buffer);

        //long *id_format1;
        long *id_format3;
        //char **name_format1;
        char **name_format3;
        //int sz1=0;
        int sz3=0;

        
        //E2SM_KPM_RANfunction_Description_t * e2smKpmRanFunctDescrip=(E2SM_KPM_RANfunction_Description_t * )calloc(1,sizeof(E2SM_KPM_RANfunction_Description_t ));
        E2SM_RC_RANFunctionDefinition_t *e2smrcRanFunctDefinition= (E2SM_RC_RANFunctionDefinition_t * )calloc(1,sizeof(E2SM_RC_RANFunctionDefinition_t));
        //E2SM_RC_RANFunctionDefinition_t * e2smrcRanFunctDefinition= 0; //(E2SM_RC_RANFunctionDefinition_t * )calloc(1,sizeof(E2SM_RC_RANFunctionDefinition_t));

        enum asn_transfer_syntax syntax;
        syntax = ATS_ALIGNED_BASIC_PER;
        asn_dec_rval_t rval =  aper_decode_complete(NULL, &asn_DEF_E2SM_RC_RANFunctionDefinition, (void**)&e2smrcRanFunctDefinition, hex_buffer, hex_len);
        //asn_dec_rval_t rval =  asn_decode(NULL, syntax, &asn_DEF_E2SM_RC_RANFunctionDefinition, (void**)&e2smrcRanFunctDefinition, hex_buffer, hex_len);

        if(rval.code == RC_OK)
        {
                fprintf(stderr,"[INFO] E2SM RC RAN Function Definiton decode successfull rval.code = %d \n",rval.code);
                fprintf(stderr,"[INFO] E2SM RC RAN Function Definiton name = %c%c\n",e2smrcRanFunctDefinition->ranFunction_Name.ranFunction_ShortName.buf[0],e2smrcRanFunctDefinition->ranFunction_Name.ranFunction_ShortName.buf[1]);
                fprintf(stderr,"[INFO] E2SM RC RAN Function Definiton OID = %c%c\n",e2smrcRanFunctDefinition->ranFunction_Name.ranFunction_E2SM_OID.buf[0],e2smrcRanFunctDefinition->ranFunction_Name.ranFunction_E2SM_OID.buf[1]);
                fprintf(stderr,"[INFO] E2SM RC RAN Function Definiton Description = %c%c\n",e2smrcRanFunctDefinition->ranFunction_Name.ranFunction_Description.buf[0],e2smrcRanFunctDefinition->ranFunction_Name.ranFunction_Description.buf[1]);
                fprintf(stderr,"[INFO] E2SM RC RAN Function Definiton num of elements = %d\n",e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.size);
                //asn_fprint(stdout, &asn_DEF_E2SM_RC_RANFunctionDefinition, e2smrcRanFunctDefinition);

                //      ric-InsertStyle-List    //
                /*
                for(int i=0; i< e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.count; i++){
                        fprintf(stderr,"[INFO] RIC INSERT style type  = %d\n",e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertStyle_Type);
                        fprintf(stderr,"[INFO] RIC INSERT style name  = %s\n",e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertStyle_Name);
                        fprintf(stderr,"[INFO] RIC INSERT action definition  = %d\n",e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_ActionDefinitionFormat_Type);

                        //      ric-InsertStyle-List            [4] Radio Access Control request        //
                        if(e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertStyle_Type == 4 ){            
                                  
                                 //    ric-InsertIndication-List       //
                                  for(int k=0; k < e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertIndication_List->list.count; k++)
                                  {
                                        //    ric-InsertIndication-List         [3] Access barring control request      //
                                        if(e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertIndication_List->list.array[k]->ric_InsertIndication_ID == 3)
                                        {
                                                //      ran-InsertIndication-RANParameter-List     //
                                                sz3 = e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertIndication_List->list.array[k]->ran_InsertIndicationParameters_List->list.count;
                                                id_format3=(long *)calloc(sz3,sizeof(long));
                                                name_format3=(char **)malloc(sz3*sizeof(char *));
                                                for(int j=0;j<sz3;j++){
                                                       id_format3[j]=e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertIndication_List->list.array[k]->ran_InsertIndicationParameters_List->list.array[j]->ranParameter_ID;
                                                       size_t bufsize=e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertIndication_List->list.array[k]->ran_InsertIndicationParameters_List->list.array[j]->ranParameter_name.size;
                                                       name_format3[j]=(char*)malloc(bufsize);
                                                       name_format3[j]=e2smrcRanFunctDefinition->ranFunctionDefinition_Insert->ric_InsertStyle_List->list.array[i]->ric_InsertIndication_List->list.array[k]->ran_InsertIndicationParameters_List->list.array[j]->ranParameter_name.buf;
                                                }
                                        }
                                  }

                        }
                }
                */
        }else{
                 //printf("[INFO] E2SM RC RAN Function Definiton decode  failed rval.code = %d \n", rval.code);
                 fprintf(stderr,"[INFO] E2SM RC RAN Function Definiton decode  failed rval.code = %d \n", rval.code);
        }
               
        fprintf(stderr,"[INFO] num elements %d\n",sz3);
        for(int i=0;i<sz3;i++){
                fprintf(stderr,"[INFO] measID format 3 %ld, measName format 3 %s\n",id_format3[i], name_format3[i]);
        }
        unsigned char bufFormat3[BUFFER_SIZE];
        size_t buf_sizeFormat3 = BUFFER_SIZE;
        
        //long ricStyleTypeFormat1 = 1;
        long ricInsertStyleTypeFormat3 = 3;
        //unsigned long granulPeriod = 10000;

        //get plmn id during run time of kpimon
        //unsigned char p[] = {0x00, 0xF1, 0x10};
        unsigned char p[] = {0x00, 0xF1, 0x10};

        //get nr cell id for 5g cell or eutra cell id for 4g cell
        //unsigned char nR []= {0x12, 0x34, 0x56, 0x00, 0x10};
        //unsigned char nR []= {0x00, 0x00, 0x01, 0x00, 0x10};

        //      Radisys 1.7.10.127    /
        unsigned char nR []= {0x00, 0x00, 0x04, 0x00, 0x10};

        //      CCRAN9          //
        //unsigned char nR []= {0x00, 0x00, 0x24, 0x00, 0x10};

        int encodedLengthFormat3 = e2sm_encode_ric_insert_definition_format3(&bufFormat3[0], &buf_sizeFormat3, name_format3, sz3, ricInsertStyleTypeFormat3, p, nR);

        printf("\n");
	int rcarrayFormat3[encodedLengthFormat3];
        for(int i=0;i<encodedLengthFormat3;i++){
                        printf("%d ",(int)bufFormat3[i]);
			rcarrayFormat3[i]=(int)bufFormat3[i];
        }
        printf("\n");               

	switch(determine){
		case 1:
			//res.array=rcarrayFormat3;
			//res.length=encodedLengthFormat3; //-8;//removing hardcoded plmn and cellid
			return res;
		case 2:
                        res.array = rcarrayFormat3;
			res.length= encodedLengthFormat3;//-8;//removing hardcoded plmn and cellid
			return res;
		case 3:
			//res.array=arrayFormat3ById;
			//res.length=encodedLengthFormat3ById;
			//return res;
		case 4:
			//res.array=arrayFormat3ByName;
			//res.length=encodedLengthFormat3ByName;
			//return res;
			break;

	}
	return res;
}

int e2sm_encode_ric_insert_definition_format3(unsigned char *buf, size_t *buf_size, char **id_tmp , size_t measIdcount, long ric_style_type,  unsigned char  *p, unsigned char *nR) {
        
        E2SM_RC_ActionDefinition_t *rcactionDef = (E2SM_RC_ActionDefinition_t *)calloc(1, sizeof(E2SM_RC_ActionDefinition_t));
        if (!rcactionDef) {
                fprintf(stderr, "alloc RIC ActionDefinition failed\n");
                return -1;
        }

        E2SM_RC_ActionDefinition_Format3_t *actionDefFor3 = (E2SM_RC_ActionDefinition_Format3_t *)calloc(1, sizeof(E2SM_RC_ActionDefinition_Format3_t));
        if (!actionDefFor3) {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ActionDefinition, rcactionDef);
                fprintf(stderr, "alloc RIC ActionDefinition failed\n");
                return -1;
        }

        E2SM_RC_ActionDefinition_Format3_Item_t **InsertInfoItem = (E2SM_RC_ActionDefinition_Format3_Item_t  **)calloc(measIdcount, sizeof(E2SM_RC_ActionDefinition_Format3_Item_t *));
        
        //long *no_label=(long *) calloc(1,sizeof(long));//not giving label to the cell metrics/// don't know its bheaviour
        //*no_label=0;
        int index = 0;
                /*      RAN Parameter Definition ID        */
        while (index < 1) {

                InsertInfoItem[index] = (E2SM_RC_ActionDefinition_Format3_Item_t *)calloc(1, sizeof(E2SM_RC_ActionDefinition_Format3_Item_t ));
                RANParameter_Definition_t *ParamDef=(RANParameter_Definition_t *)calloc(1,sizeof(RANParameter_Definition_t));
                ParamDef->ranParameter_Definition_Choice =(RANParameter_Definition_Choice_t *)calloc(1,sizeof(RANParameter_Definition_Choice_t));
                ParamDef->ranParameter_Definition_Choice->present =  RANParameter_Definition_Choice_PR_choiceLIST;

                InsertInfoItem[index]->ranParameter_ID = 1;

                char name_format_insert[100];
                strcpy(name_format_insert,"Unified Access Control Barring Info");             

                RANParameter_Name_t *ranNameParameterName = (RANParameter_Name_t *)calloc(1,sizeof(RANParameter_Name_t));
                ranNameParameterName->buf = (uint8_t *)calloc(1,strlen(name_format_insert));
                memcpy(ranNameParameterName->buf,name_format_insert,strlen(name_format_insert));
                ranNameParameterName->size = strlen(name_format_insert);

                printf("%s, Length %ld\n",ranNameParameterName->buf, ranNameParameterName->size);

                RANParameter_Definition_Choice_LIST_Item_t **RanPareameterList = (RANParameter_Definition_Choice_LIST_Item_t **)calloc(1,sizeof(RANParameter_Definition_Choice_LIST_Item_t*));
                RanPareameterList[0]  = (RANParameter_Definition_Choice_LIST_Item_t *)calloc(1,sizeof(RANParameter_Definition_Choice_LIST_Item_t));
                RanPareameterList[0]->ranParameter_name = *ranNameParameterName;
                RanPareameterList[0]->ranParameter_ID = 1;

                ParamDef->ranParameter_Definition_Choice->choice.choiceLIST = (RANParameter_Definition_Choice_LIST_t*)calloc(1,sizeof(RANParameter_Definition_Choice_LIST_t));

                if (!ParamDef || !ParamDef->ranParameter_Definition_Choice || !ParamDef->ranParameter_Definition_Choice->choice.choiceLIST)
                    printf("\nERRO\n");
                
                
                int result1 = ASN_SEQUENCE_ADD(&ParamDef->ranParameter_Definition_Choice->choice.choiceLIST->ranParameter_List, RanPareameterList[0]);
                if (result1==-1)
                {
                        fprintf(stderr,"Unable to assign memory to add labelInfoList %s\n",strerror(errno));
                        return -1;
                }
                
                printf("\n1- Sequence %d",ParamDef->ranParameter_Definition_Choice->choice.choiceLIST->ranParameter_List.list.count);
                printf("\n1- name %s\n",ParamDef->ranParameter_Definition_Choice->choice.choiceLIST->ranParameter_List.list.array[index]->ranParameter_name.buf);

                InsertInfoItem[index]->ranParameter_Definition = ParamDef;
                /*
                int result2 = ASN_SEQUENCE_ADD(&InsertInfoItem[index]->ranParameter_Definition,&ParamDef);
                if (result2==-1)
                {
                        fprintf(stderr,"result2 Unable to assign memory to add labelInfoList %s\n",strerror(errno));
                        return -1;
                }
                */
                printf("\n2- Sequence %d",InsertInfoItem[index]->ranParameter_Definition->ranParameter_Definition_Choice->choice.choiceLIST->ranParameter_List.list.count);
                printf("\n2- name %s\n",InsertInfoItem[index]->ranParameter_Definition->ranParameter_Definition_Choice->choice.choiceLIST->ranParameter_List.list.array[index]->ranParameter_name.buf);

                int result3 = ASN_SEQUENCE_ADD(&actionDefFor3->ranP_InsertIndication_List, InsertInfoItem[index]);
                if (result3==-1)
                {
                        fprintf(stderr,"Unable to assign memory to add measInfoList %s",strerror(errno));
                        return -1;
                }
             
                index++;
        }
        
        char errbuf[128];
        size_t errbuf_len = 128;

        actionDefFor3->ric_InsertIndication_ID = 0;
        printf("\nEstructura RANFunctionDefiniton\n");
        asn_fprint(stdout, &asn_DEF_E2SM_RC_ActionDefinition_Format3, actionDefFor3);
        


        rcactionDef->ric_Style_Type = 4;
        rcactionDef->ric_actionDefinition_formats.present = E2SM_RC_ActionDefinition__ric_actionDefinition_formats_PR_actionDefinition_Format3;
        rcactionDef->ric_actionDefinition_formats.choice.actionDefinition_Format3 =  actionDefFor3;  

        int ret_constr = asn_check_constraints(&asn_DEF_E2SM_RC_ActionDefinition, (void *)rcactionDef, errbuf, &errbuf_len);
        if(ret_constr){
                fprintf(stderr,"Constraints failed for encoding subscription request, %s", strerror(errno));
                return -1;
        }
        
        printf("Estructura RANFunctionDefiniton\n");
        asn_fprint(stdout, &asn_DEF_E2SM_RC_ActionDefinition, rcactionDef);
        //asn_enc_rval_t encode_result = asn_encode_to_buffer(0,ATS_ALIGNED_CANONICAL_PER,&asn_DEF_E2SM_RC_ActionDefinition,rcactionDef, buf, *buf_size);
        asn_enc_rval_t encode_result = asn_encode_to_buffer(0,ATS_ALIGNED_CANONICAL_PER,&asn_DEF_E2SM_RC_ActionDefinition_Format3, actionDefFor3, buf, *buf_size);

        if (encode_result.encoded == -1) {
                fprintf(stderr, "Cannot encode %s: %s in line %d, file %s\n", encode_result.failed_type->name, strerror(errno),  __LINE__, __FILE__);
                return -1;
        }
        else {
                fprintf(stderr, "successfully\n");
                return encode_result.encoded;
        }
}

ssize_t e2sm_encode_ric_control_header_qos(void *buffer, size_t buf_size,struct uEID *inUEID,long f1AP[],size_t f1AP_len,long e1AP[],size_t e1Ap_len,long ricControlStyleType, long ricControlActionID, void* plmnId, size_t  plmnIdSize, long ricControlDecision)
{
        fprintf(stderr,"e2SM wrapper function Entered\n");	
	fprintf(stderr,"plmn Size = %ld and aMFRegionID Size = %ld and aMFSetID_size = %ld and aMFPointer_size = %ld \n", inUEID->pLMNIdentity_size,inUEID->aMFRegionID_size,inUEID->aMFSetID_size,inUEID->aMFPointer_size);

        E2SM_RC_ControlHeader_t *controlHeaderIE = (E2SM_RC_ControlHeader_t *)calloc(1, sizeof(E2SM_RC_ControlHeader_t));
        if(!controlHeaderIE)
        {
                fprintf(stderr, "alloc E2SM_RC_ControlHeader failed\n");
                   return -1;
        }

        controlHeaderIE->ric_controlHeader_formats.present = E2SM_RC_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format1;
        //E2SM_RC_ControlHeader_Format1_t  *controlHeader_Fmt1 = (E2SM_RC_ControlHeader_Format1_t *)calloc(1, sizeof(E2SM_RC_ControlHeader_Format1_t));
	E2SM_RC_ControlHeader_Format1_t  *controlHeader_Fmt1 = NULL;
	controlHeaderIE->ric_controlHeader_formats.choice.controlHeader_Format1 = (E2SM_RC_ControlHeader_Format1_t *)calloc(1, sizeof(E2SM_RC_ControlHeader_Format1_t));
	controlHeader_Fmt1 = controlHeaderIE->ric_controlHeader_formats.choice.controlHeader_Format1;
        if(!controlHeader_Fmt1)
        {
                fprintf(stderr, "alloc E2SM_RC_ControlHeader failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                return -1;
        }
       
	controlHeader_Fmt1->ueID.present = UEID_PR_gNB_UEID;
	controlHeader_Fmt1->ueID.choice.gNB_UEID = (UEID_GNB_t *)calloc(1,sizeof(UEID_GNB_t));
	if(! controlHeader_Fmt1->ueID.choice.gNB_UEID)
	{
		ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
				fprintf(stderr, "alloc gNB_UEID failed\n");
                return -1;
	}

	asn_long2INTEGER(&controlHeader_Fmt1->ueID.choice.gNB_UEID->amf_UE_NGAP_ID,inUEID->amf_UE_NGAP_Id);

	fprintf(stderr, "e2sm_encode_ric_control_header amf_UE_NGAP_ID encoded \n");
	
	//OCTET_STRING_fromBuf(&controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.pLMNIdentity,inUEID->pLMNIdentity, inUEID->pLMNIdentity_size);

	OCTET_STRING_fromBuf(&controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.pLMNIdentity, plmnId,plmnIdSize);
	fprintf(stderr, "e2smrc_encode_ric_control_header pLMNIdentity encoded \n");

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf = (uint8_t*)calloc(1,inUEID->aMFRegionID_size);
        if(!controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                fprintf(stderr, "alloc aMFRegionID Value failed\n");
                return -1;
        }
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.size = 1;//inUEID->aMFRegionID_size;
	 int decimal_num= (int)strtol(inUEID->aMFRegionID, NULL, 2);
	 memcpy(controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf, (char*)&decimal_num,sizeof(unsigned int));
        //AMFR->size=1;
        controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.bits_unused=0;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf[0] = inUEID->aMFRegionID && 0XFF;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf[0] = *(inUEID->aMFRegionID ) & 0XFF;
	//memcpy(controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf,inUEID->aMFRegionID,inUEID->aMFRegionID_size);

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf = (uint8_t*)calloc(1, inUEID->aMFSetID_size);
        if(!controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                fprintf(stderr, "alloc aMFSetID Value failed\n");
                return -1;
        }
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.size = inUEID->aMFSetID_size;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf[0] = (inUEID->aMFSetID && 0xFF00) >> 8;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf[1] = inUEID->aMFSetID && 0XFF00 && 0X00FF;
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf[0] = (*(inUEID->aMFSetID) & 0xFFC0) >> 8;
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.bits_unused = 6;


	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf = (uint8_t*)calloc(1, inUEID->aMFPointer_size);
        if(!controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                fprintf(stderr, "alloc aMFPointer Value failed\n");
                return -1;
        }

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.size = 1;//inUEID->aMFPointer_size;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf[0] = inUEID->aMFPointer && 0XFF;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf[0] = (*(inUEID->aMFPointer) & 0xFC) >> 2;
	 int decimal_num3= (int)strtol(inUEID->aMFPointer, NULL, 2);
	 decimal_num3=decimal_num3<<2;
         memcpy(controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf, (char*)&decimal_num3,sizeof(unsigned int));

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.bits_unused = 2;


	controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List = (UEID_GNB_CU_F1AP_ID_List_t *)calloc(1,sizeof(UEID_GNB_CU_F1AP_ID_List_t));
	if(! controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List)
        {
                fprintf(stderr, "alloc gNB_CU_CP_UE_E1AP_ID_list failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                return -1;
        }
	//f1AP is an array of data
	//int n = sizeof(f1AP)/sizeof(long int);

	for(int i =0; i < f1AP_len; i++)
	{
		UEID_GNB_CU_CP_F1AP_ID_Item_t *F1AP_ID_Item = (UEID_GNB_CU_CP_F1AP_ID_Item_t *)calloc (1, sizeof(UEID_GNB_CU_CP_F1AP_ID_Item_t ));
		if(! F1AP_ID_Item)
		{
                	fprintf(stderr, "alloc UEID_GNB_CU_CP_F1AP_ID_Item failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                	return -1;
		}
 		F1AP_ID_Item->gNB_CU_UE_F1AP_ID  = f1AP[i];
		fprintf(stderr, "F1AP_id %d =%lu\n",i,*((unsigned long *) F1AP_id +i ));
		ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List->list,F1AP_ID_Item);
	}
	//F1AP_ID_Item->gNB_CU_UE_F1AP_ID  = f1AP[0];
	//ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List->list,F1AP_ID_Item);

	
	controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List = (UEID_GNB_CU_CP_E1AP_ID_List_t *)calloc(1,sizeof(UEID_GNB_CU_CP_E1AP_ID_List_t));

	if(! controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List)
	{
		fprintf(stderr, "alloc gNB_CU_CP_UE_E1AP_ID_list failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                return -1;
	}

	
	//n = sizeof(e1AP)/sizeof(long int);
	for(int i =0; i < e1Ap_len; i++)
	{
		UEID_GNB_CU_CP_E1AP_ID_Item_t *E1AP_ID_Item = (UEID_GNB_CU_CP_E1AP_ID_Item_t *)calloc (1, sizeof(UEID_GNB_CU_CP_E1AP_ID_Item_t ));
        	if(! E1AP_ID_Item)
        	{
                	fprintf(stderr, "alloc UEID_GNB_CU_CP_E1AP_ID_Item failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                	return -1;

        	}
		E1AP_ID_Item->gNB_CU_CP_UE_E1AP_ID = e1AP[i];
         	ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List->list,E1AP_ID_Item);
	//E1AP_ID_Item->gNB_CU_CP_UE_E1AP_ID = (*(unsigned long *) E1AP_id) ;
	//ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List->list,E1AP_ID_Item);
	}
	

        controlHeader_Fmt1->ric_Style_Type = ricControlStyleType;
        controlHeader_Fmt1->ric_ControlAction_ID = ricControlActionID;
        controlHeader_Fmt1->ric_ControlDecision = (long *)calloc(1, sizeof(long));
        *controlHeader_Fmt1->ric_ControlDecision = ricControlDecision;

        controlHeaderIE->ric_controlHeader_formats.choice.controlHeader_Format1 = controlHeader_Fmt1;


        fprintf(stderr, "showing xer of asn_DEF_E2SM_RC_ControlHeader data\n");
        xer_fprint(stderr, &asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
        fprintf(stderr, "\n");
        fprintf(stderr, "After xer of asn_DEF_E2SM_RC_ControlHeader data\n");
   
        asn_enc_rval_t encode_result;
        encode_result = aper_encode_to_buffer(&asn_DEF_E2SM_RC_ControlHeader, NULL, controlHeaderIE, buffer, buf_size);


        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
        if(encode_result.encoded == -1)
        {
                fprintf(stderr, "Cannot encode %s: %s, in line %d, file %s\n", encode_result.failed_type->name, strerror(errno),  __LINE__, __FILE__);
		return -1;
        }
        else
        {
               return encode_result.encoded;
        }
}

ssize_t e2sm_encode_ric_control_header(void *buffer, size_t buf_size,struct uEID *inUEID,long f1AP[],size_t f1AP_len,long e1AP[],size_t e1Ap_len,long ricControlStyleType, long ricControlActionID, void* plmnId, size_t  plmnIdSize)
{
        fprintf(stderr,"e2SM wrapper function Entered\n");	
	fprintf(stderr,"plmn Size = %ld and aMFRegionID Size = %ld and aMFSetID_size = %ld and aMFPointer_size = %ld \n", inUEID->pLMNIdentity_size,inUEID->aMFRegionID_size,inUEID->aMFSetID_size,inUEID->aMFPointer_size);

        E2SM_RC_ControlHeader_t *controlHeaderIE = (E2SM_RC_ControlHeader_t *)calloc(1, sizeof(E2SM_RC_ControlHeader_t));
        if(!controlHeaderIE)
        {
                fprintf(stderr, "alloc E2SM_RC_ControlHeader failed\n");
                   return -1;
        }

        controlHeaderIE->ric_controlHeader_formats.present = E2SM_RC_ControlHeader__ric_controlHeader_formats_PR_controlHeader_Format1;
        //E2SM_RC_ControlHeader_Format1_t  *controlHeader_Fmt1 = (E2SM_RC_ControlHeader_Format1_t *)calloc(1, sizeof(E2SM_RC_ControlHeader_Format1_t));
	E2SM_RC_ControlHeader_Format1_t  *controlHeader_Fmt1 = NULL;
	controlHeaderIE->ric_controlHeader_formats.choice.controlHeader_Format1 = (E2SM_RC_ControlHeader_Format1_t *)calloc(1, sizeof(E2SM_RC_ControlHeader_Format1_t));
	controlHeader_Fmt1 = controlHeaderIE->ric_controlHeader_formats.choice.controlHeader_Format1;
        if(!controlHeader_Fmt1)
        {
                fprintf(stderr, "alloc E2SM_RC_ControlHeader failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                return -1;
        }
       
	controlHeader_Fmt1->ueID.present = UEID_PR_gNB_UEID;
	controlHeader_Fmt1->ueID.choice.gNB_UEID = (UEID_GNB_t *)calloc(1,sizeof(UEID_GNB_t));
	if(! controlHeader_Fmt1->ueID.choice.gNB_UEID)
	{
		ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
				fprintf(stderr, "alloc gNB_UEID failed\n");
                return -1;
	}

	asn_long2INTEGER(&controlHeader_Fmt1->ueID.choice.gNB_UEID->amf_UE_NGAP_ID,inUEID->amf_UE_NGAP_Id);

	fprintf(stderr, "e2sm_encode_ric_control_header amf_UE_NGAP_ID encoded \n");
	
	//OCTET_STRING_fromBuf(&controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.pLMNIdentity,inUEID->pLMNIdentity, inUEID->pLMNIdentity_size);

	OCTET_STRING_fromBuf(&controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.pLMNIdentity, plmnId,plmnIdSize);
	fprintf(stderr, "e2smrc_encode_ric_control_header pLMNIdentity encoded \n");

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf = (uint8_t*)calloc(1,inUEID->aMFRegionID_size);
        if(!controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                fprintf(stderr, "alloc aMFRegionID Value failed\n");
                return -1;
        }
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.size = 1;//inUEID->aMFRegionID_size;
	 int decimal_num= (int)strtol(inUEID->aMFRegionID, NULL, 2);
	 memcpy(controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf, (char*)&decimal_num,sizeof(unsigned int));
        //AMFR->size=1;
        controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.bits_unused=0;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf[0] = inUEID->aMFRegionID && 0XFF;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf[0] = *(inUEID->aMFRegionID ) & 0XFF;
	//memcpy(controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFRegionID.buf,inUEID->aMFRegionID,inUEID->aMFRegionID_size);

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf = (uint8_t*)calloc(1, inUEID->aMFSetID_size);
        if(!controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                fprintf(stderr, "alloc aMFSetID Value failed\n");
                return -1;
        }
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.size = inUEID->aMFSetID_size;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf[0] = (inUEID->aMFSetID && 0xFF00) >> 8;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf[1] = inUEID->aMFSetID && 0XFF00 && 0X00FF;
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.buf[0] = (*(inUEID->aMFSetID) & 0xFFC0) >> 8;
	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFSetID.bits_unused = 6;


	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf = (uint8_t*)calloc(1, inUEID->aMFPointer_size);
        if(!controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                fprintf(stderr, "alloc aMFPointer Value failed\n");
                return -1;
        }

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.size = 1;//inUEID->aMFPointer_size;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf[0] = inUEID->aMFPointer && 0XFF;
	//controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf[0] = (*(inUEID->aMFPointer) & 0xFC) >> 2;
	 int decimal_num3= (int)strtol(inUEID->aMFPointer, NULL, 2);
	 decimal_num3=decimal_num3<<2;
         memcpy(controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.buf, (char*)&decimal_num3,sizeof(unsigned int));

	controlHeader_Fmt1->ueID.choice.gNB_UEID->guami.aMFPointer.bits_unused = 2;


	controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List = (UEID_GNB_CU_F1AP_ID_List_t *)calloc(1,sizeof(UEID_GNB_CU_F1AP_ID_List_t));
	if(! controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List)
        {
                fprintf(stderr, "alloc gNB_CU_CP_UE_E1AP_ID_list failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                return -1;
        }
	//f1AP is an array of data
	//int n = sizeof(f1AP)/sizeof(long int);

	for(int i =0; i < f1AP_len; i++)
	{
		UEID_GNB_CU_CP_F1AP_ID_Item_t *F1AP_ID_Item = (UEID_GNB_CU_CP_F1AP_ID_Item_t *)calloc (1, sizeof(UEID_GNB_CU_CP_F1AP_ID_Item_t ));
		if(! F1AP_ID_Item)
		{
                	fprintf(stderr, "alloc UEID_GNB_CU_CP_F1AP_ID_Item failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                	return -1;
		}
 		F1AP_ID_Item->gNB_CU_UE_F1AP_ID  = f1AP[i];
		fprintf(stderr, "F1AP_id %d =%lu\n",i,*((unsigned long *) F1AP_id +i ));
		ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List->list,F1AP_ID_Item);
	}
	//F1AP_ID_Item->gNB_CU_UE_F1AP_ID  = f1AP[0];
	//ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_UE_F1AP_ID_List->list,F1AP_ID_Item);

	
	controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List = (UEID_GNB_CU_CP_E1AP_ID_List_t *)calloc(1,sizeof(UEID_GNB_CU_CP_E1AP_ID_List_t));

	if(! controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List)
	{
		fprintf(stderr, "alloc gNB_CU_CP_UE_E1AP_ID_list failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                return -1;
	}

	
	//n = sizeof(e1AP)/sizeof(long int);
	for(int i =0; i < e1Ap_len; i++)
	{
		UEID_GNB_CU_CP_E1AP_ID_Item_t *E1AP_ID_Item = (UEID_GNB_CU_CP_E1AP_ID_Item_t *)calloc (1, sizeof(UEID_GNB_CU_CP_E1AP_ID_Item_t ));
        	if(! E1AP_ID_Item)
        	{
                	fprintf(stderr, "alloc UEID_GNB_CU_CP_E1AP_ID_Item failed\n");
				ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
                	return -1;

        	}
		E1AP_ID_Item->gNB_CU_CP_UE_E1AP_ID = e1AP[i];
         	ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List->list,E1AP_ID_Item);
	//E1AP_ID_Item->gNB_CU_CP_UE_E1AP_ID = (*(unsigned long *) E1AP_id) ;
	//ASN_SEQUENCE_ADD(&controlHeader_Fmt1->ueID.choice.gNB_UEID->gNB_CU_CP_UE_E1AP_ID_List->list,E1AP_ID_Item);
	}
	

        controlHeader_Fmt1->ric_Style_Type = ricControlStyleType;
        controlHeader_Fmt1->ric_ControlAction_ID = ricControlActionID;

        controlHeaderIE->ric_controlHeader_formats.choice.controlHeader_Format1 = controlHeader_Fmt1;


        fprintf(stderr, "showing xer of asn_DEF_E2SM_RC_ControlHeader data\n");
        xer_fprint(stderr, &asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
        fprintf(stderr, "\n");
        fprintf(stderr, "After xer of asn_DEF_E2SM_RC_ControlHeader data\n");
   
        asn_enc_rval_t encode_result;
        encode_result = aper_encode_to_buffer(&asn_DEF_E2SM_RC_ControlHeader, NULL, controlHeaderIE, buffer, buf_size);


        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlHeader, controlHeaderIE);
        if(encode_result.encoded == -1)
        {
                fprintf(stderr, "Cannot encode %s: %s, in line %d file %s\n", encode_result.failed_type->name, strerror(errno),  __LINE__, __FILE__);
		return -1;
        }
        else
        {
               return encode_result.encoded;
        }
}

ssize_t e2sm_encode_nrcgi(NR_CGI_t *nr_cgi, void* plmnIdValue, size_t  plmnId_size,long lNRCellId, uint8_t* buffer, size_t buf_size)
{
        nr_cgi = (NR_CGI_t*)calloc(1, sizeof(NR_CGI_t));
        if(!nr_cgi) {
                fprintf(stderr, "e2src_encode_nrcgi alloc nr_cgi failed \n");
                return -1;
        }
        OCTET_STRING_fromBuf(&nr_cgi->pLMNIdentity,plmnIdValue, plmnId_size);
        //fprintf(stderr, "encodec Plmn Id = %s  plmnIdValue %s and lNRCellId = %lu \n", nr_cgi->pLMNIdentity, plmnIdValue,lNRCellId);
        //fprintf(stderr, "encodec Plmn Id = %s  and lNRCellId = %d \n", nr_cgi->pLMNIdentity,plmnIdValue,lNRCellId);
	BIT_STRING_t *nr_cell_id = &nr_cgi->nRCellIdentity ;
               nr_cell_id->buf = (uint8_t*)calloc(1,5);
               if(nr_cell_id->buf)
               {
                   nr_cell_id->size = 5;
                   nr_cell_id->buf[0] = ((lNRCellId & 0X0FF0000000) >> 28);
                   nr_cell_id->buf[1] = ((lNRCellId & 0X000FF00000) >> 20);
                   nr_cell_id->buf[2] = ((lNRCellId & 0X00000FF000) >> 12);
                   nr_cell_id->buf[3] = ((lNRCellId & 0X0000000FF0) >> 4);
                   nr_cell_id->buf[4] = (lNRCellId & 0X000000000F) << 4;
                   nr_cell_id->bits_unused = 4;

               }

          fprintf(stderr, "showing xer of asn_DEF_NR_CGI NR_CGI_t data\n");
          xer_fprint(stderr, &asn_DEF_NR_CGI, nr_cgi);

	   asn_enc_rval_t encode_result = aper_encode_to_buffer(&asn_DEF_NR_CGI, NULL, nr_cgi, buffer, buf_size);

           if(encode_result.encoded != -1)
           {
               fprintf(stderr, "nr_cgi encodedi length = %zd \n", encode_result.encoded) ;
               return encode_result.encoded;
           }
           else
           {
               fprintf(stderr, "nr_cgi encode failed =%zd \n", encode_result.encoded) ;
               return -1 ;
           }
}

ssize_t e2sm_encode_ric_control_message(void *buffer, size_t buf_size, long targetPrimaryCell, long targetCell, long nrOrEUtraCell, long nrCGIOrECGI, void* ranParameterValue,size_t  ranParameterValue_size){

                E2SM_RC_ControlMessage_t *e2smrcRcControlMsg = (E2SM_RC_ControlMessage_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_t));
        if(!e2smrcRcControlMsg) {
            fprintf(stderr, "alloc E2SM_ControlMessage_t failed\n");
        return -1;
        }
        e2smrcRcControlMsg->ric_controlMessage_formats.present = E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format1;
    E2SM_RC_ControlMessage_Format1_t *e2smrcRcControlFormat1 = (E2SM_RC_ControlMessage_Format1_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_Format1_t));
        if(!e2smrcRcControlFormat1) {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc E2SM_ControlMessage_Format1_t failed\n");
                return -1;
        }
        RANParameter_ValueType_Choice_Structure_t *ranParameter_choice_Structure4 = (struct RANParameter_ValueType_Choice_Structure*)calloc(2, sizeof(struct RANParameter_ValueType_Choice_Structure));
                //RANParameter_STRUCTURE_t* RPS4=(RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
            //ranParameter_choice_Structure4[0]=(RANParameter_ValueType_Choice_Structure_t*)calloc(1,sizeof(RANParameter_ValueType_Choice_Structure_t));
        //ranParameter_choice_Structure4[1]=(RANParameter_ValueType_Choice_Structure_t*)calloc(1,sizeof(RANParameter_ValueType_Choice_Structure_t));
                //PLMN ################################
        //void *p={"001F01"};
                //void *nR={"12345C0010"};
//               void *z={"00"};
/*
    int newSize = strlen((char*)ranParameterValue1)  + strlen((char*)ranParameterValue2) + 2;

   // Allocate new buffer
   char * newBuffer = (char *)malloc(newSize);
   //strcpy(newBuffer,z);
   strcat(newBuffer,(char *)ranParameterValue1); // or strncat
   strcat(newBuffer,(char *)ranParameterValue2);

    //newBuffer=00001F0112345C0010;
    printf("%s\n",newBuffer);
    u_int64_t lol3 = (u_int64_t)strtoll(newBuffer, NULL, 16);

    int c0=lol3 & 0X0000000000000000FF;
    int c1=(lol3>>8) & 0X0000000000000000FF;
    int c2=(lol3>>16) & 0X0000000000000000FF;
    int c3=(lol3>>24) & 0X0000000000000000FF;
    int c4=(lol3>>32) & 0X0000000000000000FF;
    int c5=(lol3>>40) & 0X0000000000000000FF;
    int c6=(lol3>>48) & 0X0000000000000000FF;
    int c7=(lol3>>56) & 0X0000000000000000FF;
    int c8=lol3 & 0X000000000000000000;
*/
                   RANParameter_STRUCTURE_Item_t *ranParameter_structure_Item_nrcgi = (RANParameter_STRUCTURE_Item_t *)calloc(1,sizeof(RANParameter_STRUCTURE_Item_t));
        ranParameter_structure_Item_nrcgi->ranParameter_ID=4;
        RANParameter_ValueType_t* RPV_t_nrcgi=(RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
        RPV_t_nrcgi->present=RANParameter_ValueType_PR_ranP_Choice_ElementFalse;
        RANParameter_ValueType_Choice_ElementFalse_t * RPVCEF_nrcgi=(RANParameter_ValueType_Choice_ElementFalse_t *)calloc(1, sizeof(RANParameter_ValueType_Choice_ElementFalse_t));
        RANParameter_Value_t *RPV_nrcgi=(RANParameter_Value_t *)calloc(1, sizeof(RANParameter_Value_t));
        RPV_nrcgi->present=      RANParameter_Value_PR_valueOctS;



        OCTET_STRING_t *NRCGI=(OCTET_STRING_t *)calloc(1,sizeof(OCTET_STRING_t));
	OCTET_STRING_fromBuf(NRCGI, ranParameterValue,ranParameterValue_size);
        RPV_nrcgi->choice.valueOctS=*NRCGI;
        RPVCEF_nrcgi->ranParameter_value=RPV_nrcgi;
        RPV_t_nrcgi->choice.ranP_Choice_ElementFalse=RPVCEF_nrcgi;
        ranParameter_structure_Item_nrcgi->ranParameter_valueType=RPV_t_nrcgi;
        ranParameter_choice_Structure4->ranParameter_Structure = (RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
                ranParameter_choice_Structure4->ranParameter_Structure->sequence_of_ranParameters = (struct RANParameter_STRUCTURE__sequence_of_ranParameters*)calloc(1,sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
           int result1 = ASN_SEQUENCE_ADD(&ranParameter_choice_Structure4->ranParameter_Structure->sequence_of_ranParameters->list, ranParameter_structure_Item_nrcgi);
    if (result1==-1)
    {
        fprintf(stderr,"Unable to assign memory to add PLMN %s",strerror(errno));
        return -1;
    }


        RANParameter_STRUCTURE_Item_t* ranParameter_structure_Item3= (RANParameter_STRUCTURE_Item_t *)calloc(1,sizeof(RANParameter_STRUCTURE_Item_t));
        ranParameter_structure_Item3->ranParameter_ID=3;
        RANParameter_ValueType_t* RPV_t3=(RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
        RPV_t3->present=RANParameter_ValueType_PR_ranP_Choice_Structure;
        RPV_t3->choice.ranP_Choice_Structure=ranParameter_choice_Structure4;
        ranParameter_structure_Item3->ranParameter_valueType=RPV_t3;
                RANParameter_ValueType_Choice_Structure_t *ranParameter_choice_Structure3 = (struct RANParameter_ValueType_Choice_Structure*)calloc(2, sizeof(struct RANParameter_ValueType_Choice_Structure));
                ranParameter_choice_Structure3->ranParameter_Structure = (RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
        ranParameter_choice_Structure3->ranParameter_Structure->sequence_of_ranParameters= (struct RANParameter_STRUCTURE__sequence_of_ranParameters*)calloc(1,sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
                int result3 = ASN_SEQUENCE_ADD(&ranParameter_choice_Structure3->ranParameter_Structure->sequence_of_ranParameters->list, ranParameter_structure_Item3);
    if (result3==-1)
    {
        fprintf(stderr,"Unable to assign memory to add  ranParameter_structure_Item3 %s",strerror(errno));
        return -1;
    }
        RANParameter_STRUCTURE_Item_t * ranParameter_structure_Item2= (RANParameter_STRUCTURE_Item_t *)calloc(1,sizeof(RANParameter_STRUCTURE_Item_t));
        ranParameter_structure_Item2->ranParameter_ID=2;
        RANParameter_ValueType_t* RPV_t2=(RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
        RPV_t2->present=RANParameter_ValueType_PR_ranP_Choice_Structure;
        RPV_t2->choice.ranP_Choice_Structure=ranParameter_choice_Structure3;
        ranParameter_structure_Item2->ranParameter_valueType=RPV_t2;
                RANParameter_ValueType_Choice_Structure_t *ranParameter_choice_Structure2 = (struct RANParameter_ValueType_Choice_Structure*)calloc(2, sizeof(struct RANParameter_ValueType_Choice_Structure));
                 ranParameter_choice_Structure2->ranParameter_Structure = (RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
        ranParameter_choice_Structure2->ranParameter_Structure->sequence_of_ranParameters= (struct RANParameter_STRUCTURE__sequence_of_ranParameters*)calloc(1,sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
        int result4 = ASN_SEQUENCE_ADD(&ranParameter_choice_Structure2->ranParameter_Structure->sequence_of_ranParameters->list, ranParameter_structure_Item2);
    if (result4==-1)
    {
        fprintf(stderr,"Unable to assign memory to add  ranParameter_structure_Item2 %s",strerror(errno));
        return -1;
    }
        RANParameter_ValueType_t* RPV_t1=(RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
        RPV_t1->present=RANParameter_ValueType_PR_ranP_Choice_Structure;
        RPV_t1->choice.ranP_Choice_Structure=ranParameter_choice_Structure2;
                  E2SM_RC_ControlMessage_Format1_Item_t *format1item = (E2SM_RC_ControlMessage_Format1_Item_t *) calloc(1,sizeof(
                                                                             E2SM_RC_ControlMessage_Format1_Item_t));
     if(!format1item) {
             fprintf(stderr, "alloc format1item failed\n");
             ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
             return -1;
     }
        format1item->ranParameter_ID=1;
        format1item->ranParameter_valueType.present = RANParameter_ValueType_PR_ranP_Choice_Structure;
        format1item->ranParameter_valueType=*RPV_t1;
        int result5 = ASN_SEQUENCE_ADD(&e2smrcRcControlFormat1->ranP_List.list, format1item);
    if (result5==-1)
    {
        fprintf(stderr,"Unable to assign memory to add  format1item %s",strerror(errno));
        return -1;
    }
        e2smrcRcControlMsg->ric_controlMessage_formats.choice.controlMessage_Format1=e2smrcRcControlFormat1;
        asn_enc_rval_t encode_result;
    encode_result = aper_encode_to_buffer(&asn_DEF_E2SM_RC_ControlMessage, NULL, e2smrcRcControlMsg, buffer,buf_size );
        fprintf(stderr, "encoded length = %ld \n", encode_result.encoded);
    if(encode_result.encoded == -1)
    {
        fprintf(stderr, "Cannot encode %s: %s in line %d, file %s\n", encode_result.failed_type->name, strerror(errno), __LINE__, __FILE__);
        return -1;
    }
    else
     {
        xer_fprint(stderr, &asn_DEF_E2SM_RC_ControlMessage,e2smrcRcControlMsg);
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
        return encode_result.encoded;
     }


}
/*
ssize_t e2sm_encode_ric_control_message(void *buffer, size_t buf_size, long targetPrimaryCell,
                        long targetCell, long nrOrEUtraCell, long nrCGIOrECGI, void* ranParameterValue, size_t  ranParameterValue_size)
{
	fprintf(stderr, "e2sm_encode_ric_control_message \n") ;
	//NR_CGI_t *nr_cgi = NULL;
	//uint8_t nrcgiBuf[buf_size];
	//ssize_t nrcgiBuf_size,nrcgiLen;


	E2SM_RC_ControlMessage_t *e2smrcRcControlMsg = (E2SM_RC_ControlMessage_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_t));
        if(!e2smrcRcControlMsg) {
            fprintf(stderr, "alloc E2SM_ControlMessage_t failed\n");
        return -1;
        }
	 e2smrcRcControlMsg->ric_controlMessage_formats.present = E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format1;

        E2SM_RC_ControlMessage_Format1_t *e2smrcRcControlFormat1 = (E2SM_RC_ControlMessage_Format1_t*)calloc(1, sizeof(E2SM_RC_ControlMessage_Format1_t));
        if(!e2smrcRcControlFormat1) {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
            	fprintf(stderr, "alloc E2SM_ControlMessage_Format1_t failed\n");
        	return -1;
        }
	// Start Target Primary Cell
        E2SM_RC_ControlMessage_Format1_Item_t *ranParameterItem1 = (E2SM_RC_ControlMessage_Format1_Item_t *) calloc(1,sizeof(
                                                                                E2SM_RC_ControlMessage_Format1_Item_t));
        if(!ranParameterItem1) {
                fprintf(stderr, "alloc RANParameter_Item_t1 failed\n");
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                return -1;
        }

        ranParameterItem1->ranParameter_ID = targetPrimaryCell;     // Target Primary Cell ID value = 1
	ranParameterItem1->ranParameter_valueType.present = RANParameter_ValueType_PR_ranP_Choice_Structure;

	RANParameter_ValueType_Choice_Structure_t *ranParameterStructure1 = (RANParameter_ValueType_Choice_Structure_t*)calloc(1, sizeof(RANParameter_ValueType_Choice_Structure_t));
        if(!ranParameterStructure1)
        {
                fprintf(stderr, "alloc RANParameter_STRUCTURE_t1 failed\n");
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                return -1;
        }

	fprintf(stderr, "targetPrimaryCell encoded \n");

	 // Start Target Cell
        RANParameter_STRUCTURE_Item_t *ranParameterItem2 = (RANParameter_STRUCTURE_Item_t *)calloc(1,sizeof(RANParameter_STRUCTURE_Item_t));

        if(!ranParameterItem2)
        {

                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc RANParameter_Item_t2 failed\n");
                return -1;
        }

	ranParameterItem2->ranParameter_ID = targetCell;    // Target Cell ID value = 2

	RANParameter_ValueType_Choice_Structure_t *ranParameterStructure2 = (RANParameter_ValueType_Choice_Structure_t*)calloc(1, sizeof(struct RANParameter_ValueType_Choice_Structure));
        if(!ranParameterStructure2)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc RANParameter_STRUCTURE_t2 failed\n");
                return -1;
        }

	fprintf(stderr, "targetPrimaryCellId Value encoded \n");

        // Start NR Cell  (or E-UTRA Cell)
         RANParameter_STRUCTURE_Item_t *ranParameterItem3 = (RANParameter_STRUCTURE_Item_t*)calloc(1,sizeof(RANParameter_STRUCTURE_Item_t));
        if(!ranParameterItem3)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc RANParameter_Item_t3 failed\n");
                return -1;
        }

        ranParameterItem3->ranParameter_ID = nrOrEUtraCell; // NR Cell ID (or E-UTRA Cell ID) value =

	RANParameter_ValueType_Choice_Structure_t *ranParameterStructure3 = (struct RANParameter_ValueType_Choice_Structure*)calloc(1, sizeof(struct RANParameter_ValueType_Choice_Structure));
        if(!ranParameterStructure3)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc RANParameter_Item_t3 failed\n");
                return -1;
        }
	fprintf(stderr, " NR Cell ID  Value encoded \n");

	// Start NR CGI (or ECGI)
        RANParameter_STRUCTURE_Item_t *ranParameterItem4 = (RANParameter_STRUCTURE_Item_t *) calloc(1,sizeof(
                                                                        RANParameter_STRUCTURE_Item_t));
        if(!ranParameterItem4)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc RANParameter_Item_t4 failed\n");
                return -1;
        }

        ranParameterItem4->ranParameter_ID = nrCGIOrECGI;   // NR CGI ID (or ECGI ID) value =

	ranParameterItem4->ranParameter_valueType = (RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
	if(!ranParameterItem4->ranParameter_valueType)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterItem4->ranParameter_valueType failed\n");
                return -1;
	}

	ranParameterItem4->ranParameter_valueType->present = RANParameter_ValueType_PR_ranP_Choice_ElementFalse;
        ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse = (RANParameter_ValueType_Choice_ElementFalse_t *)calloc(1, sizeof(RANParameter_ValueType_Choice_ElementFalse_t));
        if(!ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse)
        {
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc RANParameter_Item_t4 failed\n");
                return -1;
        }

	ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse->ranParameter_value = (RANParameter_Value_t *)calloc(1, sizeof(RANParameter_Value_t));
	if(!ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse->ranParameter_value)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameter_value failed\n");
                return -1;
	}
        ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse->ranParameter_value->present = RANParameter_Value_PR_valueOctS;
	OCTET_STRING_fromBuf(&ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse->ranParameter_value->choice.valueOctS,ranParameterValue, ranParameterValue_size);


	fprintf(stderr, "Target Plmn Id = %s ranParameterValue and lNRCellId = %lu \n", ranParameterValue,lNRCellId);
	nrcgiLen = e2sm_encode_nrcgi(nr_cgi, ranParameterValue, ranParameterValue_size, lNRCellId,nrcgiBuf,nrcgiBuf_size);
	if(nrcgiLen == -1 )
	{
		 fprintf(stderr,"e2srmc_encode_nrcgi failed \n");
		return nrcgiLen;
	}
	OCTET_STRING_fromBuf(&ranParameterItem4->ranParameter_valueType->choice.ranP_Choice_ElementFalse->ranParameter_value->choice.valueOctS,nrcgiBuf,nrcgiLen);
	
	fprintf(stderr, " NR CGI encoded \n");

	ranParameterStructure3->ranParameter_Structure = (RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
	if(!ranParameterStructure3->ranParameter_Structure)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterStructure3->ranParameter_Structure  failed\n");
                return -1;
	}

	ranParameterStructure3->ranParameter_Structure->sequence_of_ranParameters = (struct RANParameter_STRUCTURE__sequence_of_ranParameters*)calloc(1,sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
	if(!ranParameterStructure3->ranParameter_Structure->sequence_of_ranParameters)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterStructure3->ranParameter_Structure->sequence_of_ranParameters failed\n");
                return -1;
	}



	ASN_SEQUENCE_ADD(&ranParameterStructure3->ranParameter_Structure->sequence_of_ranParameters->list, ranParameterItem4);   // NR CGI (or ECGI)
	ranParameterItem3->ranParameter_valueType = (RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
	if(!ranParameterItem3->ranParameter_valueType)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterItem3->ranParameter_valueType failed\n");
                return -1;
	}
        ranParameterItem3->ranParameter_valueType->present = RANParameter_ValueType_PR_ranP_Choice_Structure;
        ranParameterItem3->ranParameter_valueType->choice.ranP_Choice_Structure = ranParameterStructure3; // NR Cell  (or E-UTRA Cell)
	fprintf(stderr, " ranParameterStructure3 encoded \n");

	ranParameterStructure2->ranParameter_Structure = (RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
	if(!ranParameterStructure2->ranParameter_Structure)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterStructure2->ranParameter_Structure  failed\n");
                return -1;
	}

	ranParameterStructure2->ranParameter_Structure->sequence_of_ranParameters = (struct RANParameter_STRUCTURE__sequence_of_ranParameters*)calloc(1,sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
	if(!ranParameterStructure2->ranParameter_Structure->sequence_of_ranParameters)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterStructure3->ranParameter_Structure->sequence_of_ranParameters failed\n");
                return -1;
	}

        ASN_SEQUENCE_ADD(&ranParameterStructure2->ranParameter_Structure->sequence_of_ranParameters->list, ranParameterItem3);   // NR Cell  (or E-UTRA Cell)
	ranParameterItem2->ranParameter_valueType = (RANParameter_ValueType_t*)calloc(1,sizeof(RANParameter_ValueType_t));
	if(!ranParameterItem2->ranParameter_valueType)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterItem2->ranParameter_valueType failed\n");
                return -1;
	}
        ranParameterItem2->ranParameter_valueType->present = RANParameter_ValueType_PR_ranP_Choice_Structure;
        ranParameterItem2->ranParameter_valueType->choice.ranP_Choice_Structure = ranParameterStructure2; // Target Cell
	fprintf(stderr, " ranParameterStructure2 encoded \n");

	ranParameterStructure1->ranParameter_Structure = (RANParameter_STRUCTURE_t*)calloc(1,sizeof(RANParameter_STRUCTURE_t));
	if(!ranParameterStructure1->ranParameter_Structure)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterStructure1->ranParameter_Structure  failed\n");
                return -1;
	}

	ranParameterStructure1->ranParameter_Structure->sequence_of_ranParameters = (struct RANParameter_STRUCTURE__sequence_of_ranParameters*)calloc(1,sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
	if(!ranParameterStructure1->ranParameter_Structure->sequence_of_ranParameters)
	{
                ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
                fprintf(stderr, "alloc ranParameterStructure1->ranParameter_Structure->sequence_of_ranParameters failed\n");
                return -1;
	}
	fprintf(stderr, " ranParameterStructure1 encoded \n");

        ASN_SEQUENCE_ADD(&ranParameterStructure1->ranParameter_Structure->sequence_of_ranParameters->list, ranParameterItem2);   // Target Cell
        ranParameterItem1->ranParameter_valueType.choice.ranP_Choice_Structure = ranParameterStructure1; // Target Primary Cell

        ASN_SEQUENCE_ADD(&e2smrcRcControlFormat1->ranP_List.list, ranParameterItem1); // Target Primary Cell
        e2smrcRcControlMsg->ric_controlMessage_formats.choice.controlMessage_Format1 = e2smrcRcControlFormat1;


        fprintf(stderr, "showing xer of asn_DEF_E2SM_RC_ControlMessage data\n");
        xer_fprint(stderr, &asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
        fprintf(stderr, "\n");
        fprintf(stderr, "After xer of asn_DEF_E2SM_RC_ControlMessage data\n");

        asn_enc_rval_t encode_result;
        encode_result = aper_encode_to_buffer(&asn_DEF_E2SM_RC_ControlMessage, NULL, e2smrcRcControlMsg, buffer, buf_size);
        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, e2smrcRcControlMsg);
	fprintf(stderr, "encoded length = %ld \n", encode_result.encoded);
        if(encode_result.encoded == -1)
        {
                fprintf(stderr, "Cannot encode %s: %s\n", encode_result.failed_type->name, strerror(errno));
                return -1;
        }
        else
        {
                return encode_result.encoded;
        }
}
*/

E2SM_RC_ControlOutcome_t* e2sm_decode_ric_call_process_outcome(void *buffer, size_t buf_size)
{
	fprintf(stderr, "e2sm_decode_ric_call_process_outcome Enter \n");
	asn_dec_rval_t decode_result;
	E2SM_RC_ControlOutcome_t* controlOutcome = NULL;
        decode_result = aper_decode_complete(NULL, &asn_DEF_E2SM_RC_ControlOutcome, (void **)&controlOutcome, buffer, buf_size);
        if(decode_result.code == RC_OK) {
        	xer_fprint(stdout, &asn_DEF_E2SM_RC_ControlOutcome, controlOutcome);
        	return controlOutcome;
    	}
        else {
        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlOutcome, controlOutcome);
        return NULL;
        }
}

void e2sm_free_ric_call_process_outcome(E2SM_RC_ControlOutcome_t* controlOutcome) {
        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlOutcome, controlOutcome);
}

ssize_t e2sm_encode_ric_control_message_qos(
    void *buffer, size_t buf_size,
    long drb_id, long qos_flow_id, long five_qi, long priority_level)
{
    E2SM_RC_ControlMessage_t *controlMessage = (E2SM_RC_ControlMessage_t *)calloc(1, sizeof(E2SM_RC_ControlMessage_t));
    if (!controlMessage) {
        fprintf(stderr, "alloc E2SM_RC_ControlMessage_t failed\n");
        return -1;
    }

    controlMessage->ric_controlMessage_formats.present = E2SM_RC_ControlMessage__ric_controlMessage_formats_PR_controlMessage_Format1;
    E2SM_RC_ControlMessage_Format1_t *format1 = (E2SM_RC_ControlMessage_Format1_t *)calloc(1, sizeof(E2SM_RC_ControlMessage_Format1_t));
    if (!format1) {
        fprintf(stderr, "alloc E2SM_RC_ControlMessage_Format1_t failed\n");
        ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, controlMessage);
        return -1;
    }

    controlMessage->ric_controlMessage_formats.choice.controlMessage_Format1 = format1;

    // -------------------------------------------------------
    // ID 1: DRB Identification
    // -------------------------------------------------------
    E2SM_RC_ControlMessage_Format1_Item_t *drbIdItem = (E2SM_RC_ControlMessage_Format1_Item_t *)calloc(1, sizeof(E2SM_RC_ControlMessage_Format1_Item_t));
    drbIdItem->ranParameter_ID = 1;
    drbIdItem->ranParameter_valueType.present = RANParameter_ValueType_PR_ranP_Choice_ElementTrue;
    RANParameter_ValueType_Choice_ElementTrue_t *drbIdValue = (RANParameter_ValueType_Choice_ElementTrue_t *)calloc(1, sizeof(RANParameter_ValueType_Choice_ElementTrue_t));
    drbIdValue->ranParameter_value.present = RANParameter_Value_PR_valueInt;
    drbIdValue->ranParameter_value.choice.valueInt = drb_id;
    drbIdItem->ranParameter_valueType.choice.ranP_Choice_ElementTrue = drbIdValue;
    ASN_SEQUENCE_ADD(&format1->ranP_List.list, drbIdItem);

//     // -------------------------------------------------------
//     // ID 30003: QoS Configuration List
//     // -------------------------------------------------------
//     E2SM_RC_ControlMessage_Format1_Item_t *qosConfigListItem = (E2SM_RC_ControlMessage_Format1_Item_t *)calloc(1, sizeof(E2SM_RC_ControlMessage_Format1_Item_t));
//     qosConfigListItem->ranParameter_ID = 30003;
//     qosConfigListItem->ranParameter_valueType.present = RANParameter_ValueType_PR_ranP_Choice_List;
//     RANParameter_ValueType_Choice_List_t *qosConfigListValue = (RANParameter_ValueType_Choice_List_t *)calloc(1, sizeof(RANParameter_ValueType_Choice_List_t));
//     qosConfigListItem->ranParameter_valueType.choice.ranP_Choice_List = qosConfigListValue;
//     qosConfigListValue->ranParameter_List = (RANParameter_LIST_t *)calloc(1, sizeof(RANParameter_LIST_t));
//     ASN_SEQUENCE_ADD(&format1->ranP_List.list, qosConfigListItem);

//     // -------------------------------------------------------
//     // List Container (Invisible Wrapper inside ID 30003)
//     // -------------------------------------------------------
//     RANParameter_STRUCTURE_t *qosListContainer = (RANParameter_STRUCTURE_t *)calloc(1, sizeof(RANParameter_STRUCTURE_t));
//     qosListContainer->sequence_of_ranParameters = (struct RANParameter_STRUCTURE__sequence_of_ranParameters *)calloc(1, sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));
//     ASN_SEQUENCE_ADD(&qosConfigListValue->ranParameter_List->list_of_ranParameter.list, qosListContainer);

//     // -------------------------------------------------------
//     // ID 30004: QoS Flow Definition Item
//     // -------------------------------------------------------
//     RANParameter_STRUCTURE_Item_t *qosFlowDefItem = (RANParameter_STRUCTURE_Item_t *)calloc(1, sizeof(RANParameter_STRUCTURE_Item_t));
//     qosFlowDefItem->ranParameter_ID = 30004;
//     qosFlowDefItem->ranParameter_valueType = (RANParameter_ValueType_t *)calloc(1, sizeof(RANParameter_ValueType_t));
//     qosFlowDefItem->ranParameter_valueType->present = RANParameter_ValueType_PR_ranP_Choice_Structure;
//     ASN_SEQUENCE_ADD(&qosListContainer->sequence_of_ranParameters->list, qosFlowDefItem);

//     // -------------------------------------------------------
//     // ID 30004 Structure Payload
//     // -------------------------------------------------------
//     RANParameter_ValueType_Choice_Structure_t *qosFlowDefStructValue = (RANParameter_ValueType_Choice_Structure_t *)calloc(1, sizeof(RANParameter_ValueType_Choice_Structure_t));
//     qosFlowDefItem->ranParameter_valueType->choice.ranP_Choice_Structure = qosFlowDefStructValue;
//     qosFlowDefStructValue->ranParameter_Structure = (RANParameter_STRUCTURE_t *)calloc(1, sizeof(RANParameter_STRUCTURE_t));
//     qosFlowDefStructValue->ranParameter_Structure->sequence_of_ranParameters = (struct RANParameter_STRUCTURE__sequence_of_ranParameters *)calloc(1, sizeof(struct RANParameter_STRUCTURE__sequence_of_ranParameters));

//     // -------------------------------------------------------
//     // ID 30005: QoS Flow Identifier (QFI)
//     // -------------------------------------------------------
//     RANParameter_STRUCTURE_Item_t *qfiItem = (RANParameter_STRUCTURE_Item_t *)calloc(1, sizeof(RANParameter_STRUCTURE_Item_t));
//     qfiItem->ranParameter_ID = 30005;
//     qfiItem->ranParameter_valueType = (RANParameter_ValueType_t *)calloc(1, sizeof(RANParameter_ValueType_t));
//     qfiItem->ranParameter_valueType->present = RANParameter_ValueType_PR_ranP_Choice_ElementTrue;
    
//     RANParameter_ValueType_Choice_ElementTrue_t *qfiValue = (RANParameter_ValueType_Choice_ElementTrue_t *)calloc(1, sizeof(RANParameter_ValueType_Choice_ElementTrue_t));
//     qfiItem->ranParameter_valueType->choice.ranP_Choice_ElementTrue = qfiValue;
//     qfiValue->ranParameter_value.present = RANParameter_Value_PR_valueInt;
//     qfiValue->ranParameter_value.choice.valueInt = qos_flow_id;
    
//     ASN_SEQUENCE_ADD(&qosFlowDefStructValue->ranParameter_Structure->sequence_of_ranParameters->list, qfiItem);

    // Encoding section
    xer_fprint(stderr, &asn_DEF_E2SM_RC_ControlMessage, controlMessage);

    asn_enc_rval_t encode_result;
    encode_result = aper_encode_to_buffer(&asn_DEF_E2SM_RC_ControlMessage, NULL, controlMessage, buffer, buf_size);

    ASN_STRUCT_FREE(asn_DEF_E2SM_RC_ControlMessage, controlMessage);

    if (encode_result.encoded == -1) {
        fprintf(stderr, "Cannot encode %s: %s, in line %d file %s\n", encode_result.failed_type->name, strerror(errno), __LINE__, __FILE__);
        return -1;
    }

    // Manually patch the buffer header if necessary
    if (encode_result.encoded >= 3 && ((uint8_t*)buffer)[0] == 0x00) {
        fprintf(stderr, "[PATCH] Replaced header 0x00 -> 0x10\n");
        ((uint8_t*)buffer)[0] = 0x10;
    }

    return encode_result.encoded;
}