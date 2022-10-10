#!/bin/bash

LD_LIBRARY_PATH=$(pwd)/bin:$LD_LIBRARY_PATH ceps \
model/exi.events.ceps \
model/exi.grammars.ceps \
model/exi.primer.example.ceps \
 --pluginlibv2g-guru-exi-plugin.so --ppe --format ansi
