#ifndef _IRTPSTRUCTER_H_
#define _IRTPSTRUCTER_H_

/*******************************************************************************************
 *									RTP Header
 *
 * 		 0             	1               2               3
 *		 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
 *		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *		|V=2|P|X|  CC   |M|     PT      |       sequence number         |
 *		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *		|                           timestamp                           |
 *		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *		|           synchronization source (SSRC) identifier            |
 *		+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *		|            contributing source (CSRC) identifiers             |
 *		|                             ....                              |
 *		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *******************************************************************************************
 *						 SR:Sender Report RTCP Packet	
 * 
 *			 0 			     1 			   2 			   3
 *			 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	 header |V=2|P|   RC    |   PT=SR=200   | 			 length 			|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 						SSRC of sender 							|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	 sender | 				NTP timestamp, most significant word 			|
 *	   info +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 				NTP timestamp, least significant word			|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 						RTP timestamp		 					|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 					sender's packet count 						|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 					sender's octet count 						|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	 report | 				SSRC_1 (SSRC of first source) 					|
 *	  block +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *		1   | fraction lost | 		cumulative number of packets lost 		|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 			extended highest sequence number received 			|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 						interarrival jitter 					|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 							last SR (LSR) 						|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 					delay since last SR (DLSR) 					|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	report  | 				SSRC_2 (SSRC of second source) 					|
 *	 block  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *		2   : 								... 							:
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *			| 					profile-specific extensions 				|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 ********************************************************************************************
 *							RR: Receiver Report RTCP Packet
 *
 *
 *			 0 				 1 				 2 				 3
 *			 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	 header |V=2|P|    RC   |    PT=RR=201  | 			length 				|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 					SSRC of packet sender 						|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	 report | 				SSRC_1 (SSRC of first source) 					|
 *	 block  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *		1   | fraction lost | 		cumulative number of packets lost 		|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 			extended highest sequence number received 			|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 					interarrival jitter 						|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 							last SR (LSR) 						|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 					delay since last SR (DLSR) 					|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	 report | 				SSRC_2 (SSRC of second source) 					|
 *	  block +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	    2 	: 								... 							:
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *			| 					profile-specific extensions 				|
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 ********************************************************************************************
 *							SDES: Source Description RTCP Packet
 *
 *			 0 				1 				2 				3
 *			 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
 *			+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	 header |V=2|P|    SC   |  PT=SDES=202  | 			length 				|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	 chunk  | 						SSRC/CSRC_1 							|
 *	    1 	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 						SDES items 								|
 *			| 							... 								|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *	 chunk  | 						SSRC/CSRC_2 							|
 *		2   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			| 						SDES items 								|
 *			| 							... 								|
 *			+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 *********************************************************************************************
 */

namespace IObject
{
	namespace INetwork
	{
		/*
		* Current protocol version.
		*/
		#define RTP_VERSION 2
		#define RTP_SEQ_MOD (1<<16)
		#define RTP_MAX_SDES 255 /* maximum text length for SDES */
		
		typedef enum {
			RTCP_SR = 200,
			RTCP_RR = 201,
			RTCP_SDES = 202,
			RTCP_BYE = 203,
			RTCP_APP = 204
		} Rtcp_Type;
		
		typedef enum {
			RTCP_SDES_END = 0,
			RTCP_SDES_CNAME = 1,
			RTCP_SDES_NAME = 2,
			RTCP_SDES_EMAIL = 3,
			RTCP_SDES_PHONE = 4,
			RTCP_SDES_LOC = 5,
			RTCP_SDES_TOOL = 6,
			RTCP_SDES_NOTE = 7,
			RTCP_SDES_PRIV = 8
		} Rtcp_Sdes_Type;
		
		struct RTPHeader
		{
			uint8_t version:2;					/* protocol version */
			uint8_t padding:1;					/* padding flag */
			uint8_t extension:1;				/* header extension flag */
			uint8_t csrccount:4;				/* CSRC count */

			uint8_t marker:1;					/* marker bit */
			uint8_t payloadtype:7;				/* payload type */

			uint16_t sequencenumber;			/* sequence number */
			uint32_t timestamp;					/* timestamp */
			uint32_t ssrc;						/* synchronization source */
			uint32_t csrc[1]; 					/* optional CSRC list */
		};

		struct RTPExtensionHeader
		{
			uint16_t extid;
			uint16_t length;
		};

		struct RTPSourceIdentifier
		{
			uint32_t ssrc;
		};
		//RTCP header
		struct RTCPCommonHeader
		{
			uint8_t version:2;					/* protocol version */
			uint8_t padding:1;					/* padding flag */
			uint8_t count:5;					/* varies by packet type */

			uint8_t packettype;					/* RTCP packet type */
			uint16_t length;					/* pkt len in words, w/o this word */
		};

		//RR
		struct RTCPReceiverReport
		{
			uint32_t ssrc; 						/* data source being reported */
			uint8_t fractionlost;				/* fraction lost since last SR/RR */
			uint8_t packetslost[3];				/* cumul. no. pkts lost (signed!) */
			uint32_t exthighseqnr;				/* extended last seq. no. received */
			uint32_t jitter;					/* interarrival jitter */
			uint32_t lsr;						/* last SR packet from this source */
			uint32_t dlsr;						/* delay since last SR packet */
		};
		
		//SDES
		struct RTCPSDESHeader
		{
			uint8_t sdesid;						/* type of item (rtcp_sdes_type_t) */
			uint8_t length;						/* length of item (in octets) */
			char data[1]; 						/* text, not null-terminated */
		};

		
		typedef struct {
			
			RTCPCommonHeader common; 			/* common header */
			union 
			{
				/* sender report (SR) */
				struct 
				{
					uint32_t ssrc; 				/* sender generating this report */
					uint32_t ntp_sec; 			/* NTP timestamp */
					uint32_t ntp_frac;
					uint32_t rtp_ts; 			/* RTP timestamp */
					uint32_t psent; 			/* packets sent */
					uint32_t osent; 			/* octets sent */
					RTCPReceiverReport rr[1]; 	/* variable-length list */
				} sr;
					
				/* reception report (RR) */
				struct 
				{
					uint32_t ssrc; 				/* receiver generating this report */
					RTCPReceiverReport rr[1]; 	/* variable-length list */
				} rr;
				
				/* source description (SDES) */
				struct rtcp_sdes 
				{
					uint32_t src; 				/* first SSRC/CSRC */
					RTCPSDESHeader item[1]; 	/* list of SDES items */
				} sdes;
				
				/* BYE */
				struct 
				{
					uint32_t src[1]; /* list of sources */
					/* can't express trailing text for reason */
				} bye;
			}rtcp;
		}RTCPPacket;
	}
}

#endif

