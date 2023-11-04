-- (c) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- (c) Copyright 2022-2023 Advanced Micro Devices, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of AMD and is protected under U.S. and international copyright
-- and other intellectual property laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- AMD, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) AMD shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or AMD had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- AMD products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of AMD products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.
-- IP VLNV: xilinx.com:ip:xdma:4.1
-- IP Revision: 23

-- The following code must appear in the VHDL architecture header.

------------- Begin Cut here for COMPONENT Declaration ------ COMP_TAG
COMPONENT xdma_0
  PORT (
    sys_clk : IN STD_LOGIC;
    sys_rst_n : IN STD_LOGIC;
    user_lnk_up : OUT STD_LOGIC;
    pci_exp_txp : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    pci_exp_txn : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    pci_exp_rxp : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    pci_exp_rxn : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    axi_aclk : OUT STD_LOGIC;
    axi_aresetn : OUT STD_LOGIC;
    usr_irq_req : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    usr_irq_ack : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    msi_enable : OUT STD_LOGIC;
    msix_enable : OUT STD_LOGIC;
    msi_vector_width : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axil_awaddr : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axil_awprot : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axil_awvalid : OUT STD_LOGIC;
    m_axil_awready : IN STD_LOGIC;
    m_axil_wdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axil_wstrb : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axil_wvalid : OUT STD_LOGIC;
    m_axil_wready : IN STD_LOGIC;
    m_axil_bvalid : IN STD_LOGIC;
    m_axil_bresp : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axil_bready : OUT STD_LOGIC;
    m_axil_araddr : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axil_arprot : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axil_arvalid : OUT STD_LOGIC;
    m_axil_arready : IN STD_LOGIC;
    m_axil_rdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axil_rresp : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axil_rvalid : IN STD_LOGIC;
    m_axil_rready : OUT STD_LOGIC;
    s_axis_c2h_tdata_0 : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
    s_axis_c2h_tlast_0 : IN STD_LOGIC;
    s_axis_c2h_tvalid_0 : IN STD_LOGIC;
    s_axis_c2h_tready_0 : OUT STD_LOGIC;
    s_axis_c2h_tkeep_0 : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    m_axis_h2c_tdata_0 : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axis_h2c_tlast_0 : OUT STD_LOGIC;
    m_axis_h2c_tvalid_0 : OUT STD_LOGIC;
    m_axis_h2c_tready_0 : IN STD_LOGIC;
    m_axis_h2c_tkeep_0 : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    s_axis_c2h_tdata_1 : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
    s_axis_c2h_tlast_1 : IN STD_LOGIC;
    s_axis_c2h_tvalid_1 : IN STD_LOGIC;
    s_axis_c2h_tready_1 : OUT STD_LOGIC;
    s_axis_c2h_tkeep_1 : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    m_axis_h2c_tdata_1 : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axis_h2c_tlast_1 : OUT STD_LOGIC;
    m_axis_h2c_tvalid_1 : OUT STD_LOGIC;
    m_axis_h2c_tready_1 : IN STD_LOGIC;
    m_axis_h2c_tkeep_1 : OUT STD_LOGIC_VECTOR(7 DOWNTO 0) 
  );
END COMPONENT;
-- COMP_TAG_END ------ End COMPONENT Declaration ------------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

------------- Begin Cut here for INSTANTIATION Template ----- INST_TAG
your_instance_name : xdma_0
  PORT MAP (
    sys_clk => sys_clk,
    sys_rst_n => sys_rst_n,
    user_lnk_up => user_lnk_up,
    pci_exp_txp => pci_exp_txp,
    pci_exp_txn => pci_exp_txn,
    pci_exp_rxp => pci_exp_rxp,
    pci_exp_rxn => pci_exp_rxn,
    axi_aclk => axi_aclk,
    axi_aresetn => axi_aresetn,
    usr_irq_req => usr_irq_req,
    usr_irq_ack => usr_irq_ack,
    msi_enable => msi_enable,
    msix_enable => msix_enable,
    msi_vector_width => msi_vector_width,
    m_axil_awaddr => m_axil_awaddr,
    m_axil_awprot => m_axil_awprot,
    m_axil_awvalid => m_axil_awvalid,
    m_axil_awready => m_axil_awready,
    m_axil_wdata => m_axil_wdata,
    m_axil_wstrb => m_axil_wstrb,
    m_axil_wvalid => m_axil_wvalid,
    m_axil_wready => m_axil_wready,
    m_axil_bvalid => m_axil_bvalid,
    m_axil_bresp => m_axil_bresp,
    m_axil_bready => m_axil_bready,
    m_axil_araddr => m_axil_araddr,
    m_axil_arprot => m_axil_arprot,
    m_axil_arvalid => m_axil_arvalid,
    m_axil_arready => m_axil_arready,
    m_axil_rdata => m_axil_rdata,
    m_axil_rresp => m_axil_rresp,
    m_axil_rvalid => m_axil_rvalid,
    m_axil_rready => m_axil_rready,
    s_axis_c2h_tdata_0 => s_axis_c2h_tdata_0,
    s_axis_c2h_tlast_0 => s_axis_c2h_tlast_0,
    s_axis_c2h_tvalid_0 => s_axis_c2h_tvalid_0,
    s_axis_c2h_tready_0 => s_axis_c2h_tready_0,
    s_axis_c2h_tkeep_0 => s_axis_c2h_tkeep_0,
    m_axis_h2c_tdata_0 => m_axis_h2c_tdata_0,
    m_axis_h2c_tlast_0 => m_axis_h2c_tlast_0,
    m_axis_h2c_tvalid_0 => m_axis_h2c_tvalid_0,
    m_axis_h2c_tready_0 => m_axis_h2c_tready_0,
    m_axis_h2c_tkeep_0 => m_axis_h2c_tkeep_0,
    s_axis_c2h_tdata_1 => s_axis_c2h_tdata_1,
    s_axis_c2h_tlast_1 => s_axis_c2h_tlast_1,
    s_axis_c2h_tvalid_1 => s_axis_c2h_tvalid_1,
    s_axis_c2h_tready_1 => s_axis_c2h_tready_1,
    s_axis_c2h_tkeep_1 => s_axis_c2h_tkeep_1,
    m_axis_h2c_tdata_1 => m_axis_h2c_tdata_1,
    m_axis_h2c_tlast_1 => m_axis_h2c_tlast_1,
    m_axis_h2c_tvalid_1 => m_axis_h2c_tvalid_1,
    m_axis_h2c_tready_1 => m_axis_h2c_tready_1,
    m_axis_h2c_tkeep_1 => m_axis_h2c_tkeep_1
  );
-- INST_TAG_END ------ End INSTANTIATION Template ---------

-- You must compile the wrapper file xdma_0.vhd when simulating
-- the core, xdma_0. When compiling the wrapper file, be sure to
-- reference the VHDL simulation library.



