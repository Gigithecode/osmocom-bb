#ifndef _SUBSCRIBER_H
#define _SUBSCRIBER_H

/* GSM 04.08 4.1.2.2 SIM update status */
#define GSM_SIM_U0_NULL		0
#define GSM_SIM_U1_UPDATED	1
#define GSM_SIM_U2_NOT_UPDATED	2
#define GSM_SIM_U3_ROAMING_NA	3

struct gsm_sub_plmn_list {
	struct llist_head	entry;
	uint16_t		mcc, mnc;
};

struct gsm_sub_plmn_na {
	struct llist_head	entry;
	uint16_t		mcc, mnc;
	uint8_t			cause;
};

#define GSM_IMSI_LENGTH		16

struct gsm_subscriber {
	struct osmocom_ms	*ms;

	/* status */
	uint8_t			sim_valid; /* sim inserted and valid */
	uint8_t			ustate; /* update status */
	uint8_t			sim_att; /* attached state */

	/* LAI */
	uint8_t			lai_valid;
	uint16_t		lai_mcc, lai_mnc, lai_lac;

	/* IMSI */
	uint16_t		mcc, mnc;
	char 			imsi[GSM_IMSI_LENGTH];

	/* TMSI */
	uint8_t			tmsi_valid;
	uint32_t		tmsi;

	/* key */
	uint8_t			key_seq; /* ciphering key sequence number */
	uint8_t			key[32]; /* up to 256 bit */

	/* other */
	struct llist_head	plmn_list; /* PLMN Selector field */
	struct llist_head	plmn_na; /* not allowed PLMNs */
	uint8_t			t6m_hplmn; /* timer for hplmn search */

	/* special things */
	uint8_t			always_search_hplmn;
		/* search hplmn in other countries also (for test cards) */
	char			sim_name[32]; /* name to load/save sim */

	/* PLMN last registered */
	uint8_t			plmn_valid;
	uint16_t		plmn_mcc, plmn_mnc;

	/* our access */
	uint8_t			acc_barr; /* if we may access, if cell barred */
	uint16_t		acc_class; /* bitmask of what we may access */
};

int gsm_subscr_init(struct osmocom_ms *ms);
int gsm_subscr_exit(struct osmocom_ms *ms);
int gsm_subscr_testcard(struct osmocom_ms *ms, int mcc, int mnc, char *msin);
int gsm_subscr_remove(struct osmocom_ms *ms);
void new_sim_ustate(struct gsm_subscriber *subscr, int state);

#endif /* _SUBSCRIBER_H */
