#!/bin/bash

bash ./update_data.sh

python3 make_preproc.py

bash ./post.sh

bash ./make_postproc.sh