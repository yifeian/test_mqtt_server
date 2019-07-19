/*
 * mqtt.h
 *
 *  Created on: Jul 19, 2019
 *      Author: fanyifei
 */

#ifndef MQTT_H_
#define MQTT_H_


#include <stdio.h>

#define MQTT_HEADER_LEN 2
#define MQTT_ACK_LEN  4

/* Message types */
enum message_opcode {
    CONNECT     = 0x10,
    CONNACK     = 0x20,
    PUBLISH     = 0x30,
    PUBACK      = 0x40,
    PUBREC      = 0x50,
    PUBREL      = 0x60,
    PUBCOMP     = 0x70,
    SUBSCRIBE   = 0x80,
    SUBACK      = 0x90,
    UNSUBSCRIBE = 0xA0,
    UNSUBACK    = 0xB0,
    PINGREQ     = 0xC0,
    PINGRESP    = 0xD0,
    DISCONNECT  = 0xE0
};


enum message_type {
    CONNECT_TYPE     = 1,
    CONNACK_TYPE     = 2,
    PUBLISH_TYPE     = 3,
    PUBACK_TYPE      = 4,
    PUBREC_TYPE      = 5,
    PUBREL_TYPE      = 6,
    PUBCOMP_TYPE     = 7,
    SUBSCRIBE_TYPE   = 8,
    SUBACK_TYPE      = 9,
    UNSUBSCRIBE_TYPE = 10,
    UNSUBACK_TYPE    = 11,
    PINGREQ_TYPE     = 12,
    PINGRESP_TYPE    = 13,
    DISCONNECT_TYPE  = 14
};


enum qos_level { AT_MOST_ONCE, AT_LEAST_ONCE, EXACTLY_ONCE };

union mqtt_header{
	unsigned char byte;
	struct {
		unsigned retain :1;
		unsigned qos :2;
		unsigned dup :1;
		unsigned type :4;
	}bits;
};


struct mqtt_connect{

	union mqtt_header header;

	union {
		unsigned char byte;
		struct{
            int reserverd : 1;
            unsigned clean_session : 1;
            unsigned will : 1;
            unsigned will_qos : 2;
            unsigned will_retain : 1;
            unsigned password : 1;
            unsigned username : 1;
		}bits;
	};

    struct {
        unsigned short keepalive;
        unsigned char *client_id;
        unsigned char *username;
        unsigned char *password;
        unsigned char *will_topic;
        unsigned char *will_message;
    } payload;
};

struct mqtt_connack{
	union mqtt_header header;
	union{
		unsigned char byte;
		struct{
			unsigned session_present :1;
			unsigned reserved :7;
		}bits;
	};
	unsigned char rc;
};

struct mqtt_subscribe {
	union mqtt_header header;
	unsigned short pkt_id;
	unsigned short tuples_len;
	struct{
		unsigned short topic_len;
		unsigned char *topic;
		unsigned qos;
	}*tuples;
};

struct mqtt_unsubscribe {
	union mqtt_header header;
	unsigned short pkt_id;
	unsigned short tuples_len;
	struct{
		unsigned short topic_len;
		unsigned char *topic;
	}*tuples;
};

struct mqtt_suback{
	union mqtt_header header;
	unsigned short pk_id;
	unsigned short rcslen;
	unsigned char *rcs;
};

struct mqtt_publish {

    union mqtt_header header;

    unsigned short pkt_id;

    unsigned short topiclen;
    unsigned char *topic;
    unsigned short payloadlen;
    unsigned char *payload;
};


struct mqtt_ack {

    union mqtt_header header;

    unsigned short pkt_id;
};

typedef struct mqtt_ack mqtt_puback;
typedef struct mqtt_ack mqtt_pubrec;
typedef struct mqtt_ack mqtt_pubrel;
typedef struct mqtt_ack mqtt_pubcomp;
typedef struct mqtt_ack mqtt_unsuback;
typedef union mqtt_header mqtt_pingreq;
typedef union mqtt_header mqtt_pingresp;
typedef union mqtt_header mqtt_disconnect;

union mqtt_packet {

    struct mqtt_ack ack;
    union mqtt_header header;
    struct mqtt_connect connect;
    struct mqtt_connack connack;
    struct mqtt_suback suback;
    struct mqtt_publish publish;
    struct mqtt_subscribe subscribe;
    struct mqtt_unsubscribe unsubscribe;

};


#endif /* MQTT_H_ */
