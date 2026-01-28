Guide to spinning up a vm to test kernel modules.

The assumption is that the host is running linux, in this case ill be using Ubuntu24.04

we will be using KVM + virt-manager to manage our virtual machine.

1. Check hardware virtualization support
    `egrep -c '(vmx|svm)' /proc/cpuinfo`
    if the result is 0 -> virtualization is disabled in the BIOS
    if >= 1 -> you're good.

    Also check KVM
    `lsmod | grep kvm` 

2.  Install KVM + virt-manager
    `sudo apt install`
    `sudo apt install -y qemu-kvm libvirt-daemon-system libvirt-clients virt-manager bridge-utils`

    Enable and start libvirt:
    `sudo systemctl enable libvirtd`
    `sudo systemctl start libvirtd`

    Add yourself to the group:
    `sudo usermod -aG libvirt,kvm $USER`
    `newgrp libvirt`

     Log out and back in !!!

3. Download Ubuntu ISO

    Get whatever version you would like
`wget https://releases.ubuntu.com/24.04.3/ubuntu-24.04.3-live-server-amd64.iso`

*make sure virtualization is enabled in the BIOS or the next step will fail*

4. Create the VM

    Launch manager:
    `virt-manager`

    Now in the GUI we need to
    a. Create new VM
    b. Local install media -> select ISO
    c. OS type: Linux (auto)
    d. allocate resources -> 8GB RAM
                          -> 8 CPU cores
    e. Storage -> 40-80 GB
    f.Network: NAT is fine
    g. Finish -> boot installer


