#!/bin/bash

SCRIPT_DIR=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
echo SCRIPT_DIR=${SCRIPT_DIR}
PYTHON=/home/rajatgirotra/tools/python/3.6.2/bin/python3

# Image resolution we want to use, bigger the pixel size we choose, more will be the processing time
export IMAGE_SIZE=224

# Relative size of the mobilenet model we want to use, bigger the size, more will be the processing time
export ARCHITECTURE="mobilenet_0.50_${IMAGE_SIZE}"

# Now start tensorboard, which is an application which comes with tensorflow. This is used to monitor the training
# process
# Do "tensorboard --logdir tf_files/training_summaries &" from the command line

pushd ${SCRIPT_DIR}/tensorflow-for-poets-2

${PYTHON} -m scripts.retrain \
  --bottleneck_dir=tf_files/bottlenecks \
  --how_many_training_steps=500 \
  --model_dir=tf_files/models/ \
  --summaries_dir=tf_files/training_summaries/${ARCHITECTURE} \
  --output_graph=tf_files/retrained_graph.pb \
  --output_labels=tf_files/retrained_labels.txt \
  --architecture=${ARCHITECTURE} \
  --image_dir=tf_files/flower_photos

# Testing Predictions
${PYTHON} -m scripts.label_image \
    --graph=tf_files/retrained_graph.pb \
    --image=tf_files/flower_photos/daisy/21652746_cc379e0eea_m.jpg
