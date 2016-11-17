/*
 * Copyright 2016 <Admobilize>
 * MATRIX Labs  [http://creator.matrix.one]
 * This file is part of MATRIX Creator MALOS
 *
 * MATRIX Creator MALOS is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SRC_DRIVER_SERVO_H_
#define SRC_DRIVER_SERVO_H_

#include "./malos_wishbone_base.h"
#include "matrix_hal/wishbone_bus.h"
#include "matrix_hal/gpio_control.h"

const char kServoDriverName[] = "Servo";

namespace matrix_malos {

class ServoDriver : public MalosWishboneBase {
 public:
  ServoDriver() : MalosWishboneBase(kServoDriverName) {
    SetProvidesUpdates(false);
    SetNeedsKeepalives(false);
    SetNotesForHuman("Write-read. Servo handler. In development");
  }

  // Receive a copy of the shared wishbone bus. Not owned.
  void SetupWishboneBus(matrix_hal::WishboneBus* wishbone) override {
    gpio_.reset(new matrix_hal::GPIOControl);
    gpio_->Setup(wishbone);
  }

  // Read configuration of Servo command
  bool ProcessConfig(const DriverConfig& config) override;

 private:
  // GPIO control
  std::unique_ptr<matrix_hal::GPIOControl> gpio_;
};

}  // namespace matrix_malos

#endif  // SRC_DRIVER_SERVO_H_
