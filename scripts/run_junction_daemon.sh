#!/bin/bash
if [ -z "$JUNCTION_DIR" ]; then
	echo JUNCTION_DIR is not set
	exit 1
fi
if [ -z "$NET_IFACE_PCI" ]; then
	echo NET_IFACE_PCI is not set
	exit 1
fi
sudo $JUNCTION_DIR/lib/caladan/scripts/setup_machine.sh nouintr
sudo $JUNCTION_DIR/lib/caladan/iokerneld ias no_hw_qdel nicpci $NET_IFACE_PCI

