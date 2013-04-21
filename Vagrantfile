# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant::Config.run do |config|
  config.vm.box = "ubuntu-quantal-server-i386"
  config.vm.box_url = "http://cloud-images.ubuntu.com/vagrant/quantal/current/quantal-server-cloudimg-i386-vagrant-disk1.box"

  # Boot with a GUI so you can see the screen. (Default is headless)
  # config.vm.boot_mode = :gui
   config.vm.provision :shell, :path => "run_setup_as_user.sh"
  
  
end


#Vagrant.configure("2") do |config|
  # other config here
  #config.vm.provision :shell, :path => "run_setup_as_user.sh"
#end
