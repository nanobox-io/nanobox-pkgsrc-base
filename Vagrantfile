# -*- mode: ruby -*-
# vi: set ft=ruby :

# determine pkgsrc-lite directory
[
  '../../nanobox-pkgsrc-lite',
  '../../pkgsrc-lite',
  '../.pkgsrc-lite'
].each do |candidate|
  path = File.expand_path(candidate, __FILE__)
  if ::File.exists? path
    $pkgsrc = path
  end  
end

# if pkgsrc-lite does not exist, let's fetch it now
if not $pkgsrc
  $pkgsrc = File.expand_path('../.pkgsrc-lite', __FILE__)
  clone_url = 'https://github.com/pagodabox/nanobox-pkgsrc-lite.git'

  stdout_sync = STDOUT.sync
  stderr_sync = STDERR.sync
  STDOUT.sync = STDERR.sync = true
  puts "pagodabox/nanobox-pkgsrc-lite is required to build packages, cloning into .pkgsrc-lite..."

  IO.popen "git clone #{clone_url} #{$pkgsrc}" do |out|
    until out.eof?
      puts f.gets
    end
  end

  STDOUT.sync = stdout_sync
  STDERR.sync = stderr_sync
end

# create required directories for local cache
['.distfiles', '.packages'].each do |cache|
  path = File.expand_path("../#{cache}", __FILE__)
  if not ::File.exists? path
    ::FileUtils.mkdir_p path
  end
end

Vagrant.configure('2') do |config|
  config.vm.provider 'virtualbox' do |v|
    v.memory = 4096
    v.cpus   = 4
  end

  config.vm.network "private_network", type: "dhcp"

  config.vm.define "Ubuntu" do |ubuntu|
    ubuntu.vm.box = 'ubuntu/trusty64'
  end

  # config.vm.define "SmartOS" do |smartos|
  #   smartos.vm.box = 'livinginthepast/smartos-base64'
  #   smartos.vm.network "private_network", ip: "33.33.33.10"
  #   smartos.vm.communicator = 'smartos'
  #   smartos.ssh.insert_key = false
  #   smartos.global_zone.platform_image = 'latest'
  #   smartos.zone.name = 'base64'
  #   smartos.zone.brand = 'joyent'
  #   smartos.zone.image = '0edf00aa-0562-11e5-b92f-879647d45790'
  #   smartos.zone.memory = 4096
  #   smartos.zone.disk_size = 20
  # end

  nanobox_user = ENV["NANOBOX_USER"] || 'nanobox'
  nanobox_project = ENV["NANOBOX_BASE_PROJECT"] || 'base'
  nanobox_secret = ENV["NANOBOX_#{nanobox_user.upcase}_#{nanobox_project.upcase}_SECRET"]

  # cache
  config.vm.synced_folder "./.distfiles", "/content/distfiles", type: "nfs"
  config.vm.synced_folder "./.packages", "/content/packages", type: "nfs"

  # pkgsrc framework
  config.vm.synced_folder $pkgsrc, "/content/pkgsrc", type: "nfs"
  # package definitions
  config.vm.synced_folder ".", "/content/pkgsrc/base", type: "nfs"

  config.vm.provision "shell", inline: <<-SCRIPT
    echo # Vagrant environment variables > /etc/profile.d/vagrant.sh
    echo export NANOBOX_USER=#{nanobox_user} >> /etc/profile.d/vagrant.sh
    echo export NANOBOX_PROJECT=#{nanobox_project} >> /etc/profile.d/vagrant.sh
    echo export NANOBOX_SECRET=#{nanobox_secret} >> /etc/profile.d/vagrant.sh
    echo umask 022 >> /etc/profile.d/vagrant.sh
    chmod +x /etc/profile.d/vagrant.sh
  SCRIPT

end