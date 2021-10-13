#!/bin/bash

lsof -p $1 | grep -E 'CHR|FIFO'