#include "spi_quad_packet.h"
#include "driver/spi_master.h"
#include "quad_crc.h"

uint32_t packet_compute_CRC(spi_packet *packet) {
  return CRC_compute((void*) packet, sizeof(spi_packet) - sizeof(uint32_t));
}

bool packet_check_CRC(spi_packet *packet) {
    return (packet_compute_CRC(packet) == packet->CRC);
}

void packet_set_CRC(spi_packet *packet) {
	packet->CRC = packet_compute_CRC(packet);
	uint16_t *test = &(packet->CRC);
    test[0] = SPI_SWAP_DATA_RX(test[0], 16);
    test[1] = SPI_SWAP_DATA_RX(test[1], 16);
    packet->CRC = SPI_SWAP_DATA_RX(packet->CRC, 32);
}