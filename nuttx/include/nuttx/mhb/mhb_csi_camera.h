/*
 * Copyright (c) 2016 Motorola Mobility, LLC.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MHB_CSI_CAMERA_H
#define MHB_CSI_CAMERA_H

int mhb_camera_i2c_read(uint16_t i2c_addr,
                        uint8_t *addr, int addr_len,
                        uint8_t *data, int data_len);
int mhb_camera_i2c_write(uint16_t i2c_addr,
                         uint8_t *addr, int addr_len);
int mhb_camera_i2c_read_reg1(uint16_t i2c_addr, uint16_t regaddr, uint8_t *value);
int mhb_camera_i2c_read_reg2(uint16_t i2c_addr, uint16_t regaddr, uint16_t *value);
int mhb_camera_i2c_read_reg4(uint16_t i2c_addr, uint16_t regaddr, uint32_t *value);
int mhb_camera_i2c_read_reg2_16(uint16_t i2c_addr, uint16_t regaddr, uint16_t *value);
int mhb_camera_i2c_read_reg4_16(uint16_t i2c_addr, uint16_t regaddr, uint32_t *value);
int mhb_camera_i2c_write_reg1(uint16_t i2c_addr, uint16_t regaddr, uint8_t data);
int mhb_camera_i2c_write_reg2(uint16_t i2c_addr, uint16_t regaddr, uint16_t data);
int mhb_camera_i2c_write_reg4(uint16_t i2c_addr, uint16_t regaddr, uint32_t data);
int mhb_camera_i2c_write_reg2_16(uint16_t i2c_addr, uint16_t regaddr, uint16_t data);
int mhb_camera_i2c_write_reg4_16(uint16_t i2c_addr, uint16_t regaddr, uint32_t data);

int _mhb_camera_soc_enable();
int _mhb_camera_soc_disable();
int _mhb_camera_stream_enable();
int _mhb_camera_stream_configure();
int _mhb_camera_stream_disable();
int _mhb_camera_init(struct device *dev);
uint8_t _mhb_camera_get_csi_rx_lanes(const void *udata);

#endif