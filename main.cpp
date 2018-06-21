//  File:   main.cpp
//  Performs initialization then starts the print engine and event handler
//
//  This file is part of the Ember firmware.
//
//  Copyright 2015 Autodesk, Inc. <http://ember.autodesk.com/>
//    
//  Authors:
//  Richard Greene
//  Jason Lefley
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  THIS PROGRAM IS DISTRIBUTED IN THE HOPE THAT IT WILL BE USEFUL,
//  BUT WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED WARRANTY OF
//  MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  SEE THE
//  GNU GENERAL PUBLIC LICENSE FOR MORE DETAILS.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream> 
#include <string>
#include <utils.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdexcept>
#include <Magick++.h>

#include <PrintEngine.h>
#include <EventHandler.h>
#include <TerminalUI.h>
#include <Logger.h>
#include "Logger.h"
#include <NetworkInterface.h>
#include <CommandInterpreter.h>
#include <Settings.h>
#include <MessageStrings.h>
#include <Hardware.h>
#include <MotorController.h>
#include <Filenames.h>

#include "StandardIn.h"
#include "CommandPipe.h"
#include "PrinterStatusQueue.h"
#include "Timer.h"
#include "I2C_Resource.h"
#include "GPIO_Interrupt.h"
#include "GPIO.h"
#include "Signals.h"
#include "UdevMonitor.h"
#include "I2C_Device.h"
#include "I_I2C_Device.h"
#include "Projector.h"
#include "HardwareFactory.h"

using namespace std;

// command line argument to suppress use of stdin & stdout
constexpr const char* NO_STDIO = "--nostdio";

// for setting DMA priority to avoid video flicker
constexpr unsigned long MAP_SIZE = 4096UL;
constexpr unsigned long MAP_MASK = (MAP_SIZE - 1);
constexpr off_t REG_PR_OLD_COUNT = 0x4c000054;
constexpr unsigned long PR_OLD_COUNT_VALUE = 0x00FFFFF10;
int main(int argc, char** argv) 
{
    try
    {
        I2C_Device projectorI2cDevice(PROJECTOR_SLAVE_ADDRESS,
                I2C2_PORT);
        Projector projector(projectorI2cDevice);
	projector.TurnLEDOn();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}

