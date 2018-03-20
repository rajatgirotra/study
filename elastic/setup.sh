#!/bin/bash
SCRIPTS_DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
echo "SCRIPTS_DIR = ${SCRIPTS_DIR}"

INSTALL_ROOT=/home/rajatgirotra/tools/elk
rm -rf ${INSTALL_ROOT}
mkdir -p ${INSTALL_ROOT}

ES_VERSION=6.2.2
ES_INSTALL_ROOT=${INSTALL_ROOT}/elasticsearch-${ES_VERSION}
ES_ARTIFACT=elasticsearch-${ES_VERSION}.tar.gz
ES_URL=https://artifacts.elastic.co/downloads/elasticsearch/${ES_ARTIFACT}

KIBANA_VERSION=6.2.2
KIBANA_INSTALL_ROOT=${INSTALL_ROOT}/kibana-${KIBANA_VERSION}-linux-x86_64
KIBANA_ARTIFACT=kibana-${KIBANA_VERSION}-linux-x86_64.tar.gz
KIBANA_URL=https://artifacts.elastic.co/downloads/kibana/${KIBANA_ARTIFACT}

LS_VERSION=6.2.2
LS_INSTALL_ROOT=${INSTALL_ROOT}/logstash-${LS_VERSION}
LS_ARTIFACT=logstash-${LS_VERSION}.tar.gz
LS_URL=https://artifacts.elastic.co/downloads/logstash/${LS_ARTIFACT}

FILEBEAT_VERSION=6.2.2
FILEBEAT_INSTALL_ROOT=${INSTALL_ROOT}/filebeat-${FILEBEAT_VERSION}-linux-x86_64
FILEBEAT_ARTIFACT=filebeat-${FILEBEAT_VERSION}-linux-x86_64.tar.gz
FILEBEAT_URL=https://artifacts.elastic.co/downloads/beats/filebeat/${FILEBEAT_ARTIFACT}


cd $(dirname ${INSTALL_ROOT})
rm -f ${ES_ARTIFACT}
rm -f ${KIBANA_ARTIFACT}
rm -f ${LS_ARTIFACT}
rm -f ${FILEBEAT_ARTIFACT}
wget ${ES_URL}
wget ${KIBANA_URL}
wget ${LS_URL}
wget ${FILEBEAT_URL}

# untar elastic and kibana
tar xvf ${ES_ARTIFACT} -C ${INSTALL_ROOT}
tar xvf ${KIBANA_ARTIFACT} -C ${INSTALL_ROOT}
tar xvf ${LS_ARTIFACT} -C ${INSTALL_ROOT}
tar xvf ${FILEBEAT_ARTIFACT} -C ${INSTALL_ROOT}

# enable elasticsearch.url in kibana config
KIBANA_CONFIG=${KIBANA_INSTALL_ROOT}/config/kibana.yml
sed -i.bak 's/#elasticsearch.url/elasticsearch.url/g' ${KIBANA_CONFIG}
