/************************************************************************/
/*      Inc            Author           Date                            */
/*----------------------------------------------------------------------*/
/*    fullhan        benbiao.luo      2022.05.20                        */
/************************************************************************/


#ifndef FHSES_PARAM_
#define FHSES_PARAM_

/*AEC parameter*/
typedef struct _aecParam
{	
	unsigned short BNG_FLAG;
	unsigned short AEC_DELAY_MS;     //echo delay in ms Q0
	unsigned short AEC_ECSTART_THR;  //far end signal amp threshold for the AEC  Q15
	unsigned short AEC_MIU;          //adaptive filter update step Q15
	unsigned short NLP_LEVEL;        //NLP level Q0
	unsigned short NLP_GAMMA;        //smooth factor Q14
	unsigned short POST_FILTER_SWITCH; //Q0
	unsigned short ECHO_ON_FR_SWITCH;  //Q0
	unsigned short ERLE_THR1;        //Q14
	unsigned short ERLE_SUBTHR1;     //Q14
	unsigned short ERLE_THR2;        //Q14
	unsigned short ERLE_SUBTHR2;     //Q14
	unsigned short POS_S;            //Q0
	unsigned short POS_BIT;          //Q0 postfilter bit threshold,the large,echo suppress hard (1~10:3)
	unsigned short REVERBERATION;    //Q0 length(frame) of the reverberation (0~100:0)
	unsigned short REV_SMOOTH;       //Q14 the large,the reverberation is suppressed hard (0~16384:16300)
	unsigned short TX_RX_RATIO[12];  //ratio between near_end signal with far_end signal
	/*DTD*/
	unsigned short DTD_SWITCH;
	unsigned short DTD_THR;       //Q14
	unsigned short DTD_GAIN;      //Q0
	unsigned short NON_DTD_GAIN;  //Q0
}aecParam;

/*ANC parameter*/
typedef struct _ancParam
{
	unsigned short ANC_LEVEL;     //Q0
	unsigned short BGNS_SWITCH;   //sub_band noise suppression switch Q0
	unsigned short BGNS_GAIN_HF;  //sub_band noise suppression gain factor of high_fre Q14
	unsigned short BGNS_GAIN_LF;  //sub_band noise suppression gain factor of low_fre Q14
}ancParam;

/*AGC parameter*/
typedef struct _agcParam
{
	unsigned short FIXED_GAIN;
	unsigned short TARGETDBFS;
	unsigned short GAINDB;
	unsigned short AGC_START_THR;  //the signal which energy below the thr will be suppressed Q30 
	unsigned short AGC_SUPRESS;    //suppress the small signal target gain Q14
	unsigned short AGC_UNLIMITED_FLAG;  //0:signal above targetdB is constrained  1:signal above targetdB is not constrained 
}agcParam;

/*DOA parameter*/
typedef struct _doaParam
{
	short          DOA_LEVEL;
	short          DOA_DELAY[3];
	short          DOA_MIC_LOC[12]; //the location of each microphone. Q10  unit:meter
}doaParam;

/*EQ in frequency parameter*/
typedef struct _eqfParam
{
	short          EQF_bin_G[14];
}eqfParam;

/*EQ in time parameter*/
typedef struct _eqt_SubParam
{
	unsigned short EQT_FILTER_F0;// Q0 when fs==8k F0 shoud be [50,3750];when fs==16k,F0 should be[100,7500];
	unsigned short EQT_FILTER_Q;     //Q8 Q should not be 0
	short          EQT_FILTER_GAIN_DB; //Q8
}eqt_SubParam;
typedef struct _eqtParam
{
	unsigned short EQT_FILTER_NUM;//Q0 
	eqt_SubParam eqt_sub_param[8];
}eqtParam;



typedef struct _hpfParam
{
	short          HPF_MODE;
}hpfParam;

/*howling suppress parameter*/
typedef struct _howlParam
{
	unsigned short HOWL_MC_THR1;  //Q0
	unsigned short HOWL_MC_THR2;  //Q0
	unsigned short HOWL_MC_THR3;  //Q0
	unsigned short HOWL_THR;      //Q0
}howlParam;

/*SWS_AI*/
typedef struct _ainsParam
{
	unsigned short SWS_GAIN_SMOOTH_ALPHA;
	unsigned short SWS_GAIN_BETA;
	unsigned short SWS_GAIN_MIN;
}ainsParam;

/*WNS*/
typedef struct _wnsParam
{
	unsigned short WNS_MC_NUM;
	unsigned short WNS_MC_THR;
	unsigned short WNS_BIN1_THR;
	unsigned short WNS_GAIN_LIMIT;
	unsigned short WNS_LEVEL;
}wnsParam;

typedef struct _alcParam
{
	short          ALC_GAIN;
}alcParam;

typedef struct 
{
	unsigned short aec_flag; //acoustic echo cancellation switch Q0
	unsigned short anc_flag;    //auto noise cancellation switch Q0
	unsigned short agc_flag;    //auto gain control switch Q0
	unsigned short doa_flag;    //delay of arrival and beamforming switch Q0
	unsigned short eqf_flag;     //freq domain equalizer switch Q0
	unsigned short eqt_flag;	//time domain equlizer switch Q0
	unsigned short hpf_flag;  //high_pass_filter switch Q0
	unsigned short howl_flag;   //Q0
	unsigned short ains_flag;
	unsigned short wns_flag;  //WNS_FLAG=2,dual_mic wind suppress 
	unsigned short aivad_flag;
	unsigned short alc_flag;    //Q0 alc gain in db
	aecParam       aecParam;
	ancParam       ancParam;
	agcParam       agcParam;
	doaParam       doaParam;
	eqfParam       eqfParam;
	eqtParam       eqtParam;
	hpfParam       hpfParam;
	howlParam      howlParam;
	ainsParam      ainsParam;
	wnsParam       wnsParam;
	alcParam       alcParam;
}FH_AC_SesParam;


#endif
