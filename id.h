#ifndef ID_H
#define ID_H

/**
 * @brief Bitmask indicating the ID field.
 */
#define ID_MASK 0xFFFF
/**
 * @brief Bitmask indicating the reviewer.
 */
#define REVIEWER_MASK 0x10000
/**
 * @brief Bitmask indicating the primary topic identifier.
 */
#define PRIMARY_TOPIC_MASK 0x20000
/**
 * @brief Bitmask indicating the secondary topic identifier.
 */
#define SECONDARY_TOPIC_MASK 0x40000
/**
 * @brief Bitmask indicating a source connection.
 */
#define SOURCE_CONNECTED_MASK 0x80000
/**
 * @brief Bitmask indicating a source node.
 */
#define SOURCE_ID 0x100000
/**
 * @brief Bitmask indicating a sink node.
 */
#define SINK_ID 0x200000

#endif 