/*
modification history
--------------------
01a,06nov09,m_y  added.
*/

/*
DESCRIPTION

This file contains the data structures used by GPT 
(Globally Unique Identifier Partition Table).

*/

#ifndef _UUID_H_
#define	_UUID_H_

#include <sys/cdefs.h>

/* Length of a node address (an IEEE 802 address). */
#define	_UUID_NODE_LEN		6

/*
 * See also:
 *      http://www.opengroup.org/dce/info/draft-leach-uuids-guids-01.txt
 *      http://www.opengroup.org/onlinepubs/009629399/apdxa.htm
 *
 * A DCE 1.1 compatible source representation of UUIDs.
 */
struct uuid
    {
    uint32_t	time_low;
    uint16_t	time_mid;
    uint16_t	time_hi_and_version;
    uint8_t		clock_seq_hi_and_reserved;
    uint8_t		clock_seq_low;
    uint8_t		node[_UUID_NODE_LEN];
    };

/* XXX namespace pollution? */
typedef struct uuid uuid_t;

/*
 * This implementation mostly conforms to the DCE 1.1 specification.
 * See Also:
 *	uuidgen(1), uuidgen(2), uuid(3)
 */

/* Status codes returned by the functions. */
#define	uuid_s_ok			0
#define	uuid_s_bad_version		1
#define	uuid_s_invalid_string_uuid	2
#define	uuid_s_no_memory		3

int32_t	uuid_compare(const uuid_t *, const uuid_t *, uint32_t *);
void	uuid_create(uuid_t *, uint32_t *);
void	uuid_create_nil(uuid_t *, uint32_t *);
int32_t	uuid_equal(const uuid_t *, const uuid_t *, uint32_t *);
void	uuid_from_string(const char *, uuid_t *, uint32_t *);
uint16_t uuid_hash(const uuid_t *, uint32_t *);
int32_t	uuid_is_nil(const uuid_t *, uint32_t *);
void	uuid_to_string(const uuid_t *, char *, uint32_t *);
void	uuid_enc_le(void *, const uuid_t *);
void	uuid_dec_le(const void *, uuid_t *);
void	uuid_enc_be(void *, const uuid_t *);
void	uuid_dec_be(const void *, uuid_t *);


#endif /* _UUID_H_ */

