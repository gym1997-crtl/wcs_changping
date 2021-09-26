/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50721
Source Host           : localhost:3306
Source Database       : wcs_zc9

Target Server Type    : MYSQL
Target Server Version : 50721
File Encoding         : 65001

Date: 2021-09-26 10:17:59
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for a_wcs_table_list
-- ----------------------------
DROP TABLE IF EXISTS `a_wcs_table_list`;
CREATE TABLE `a_wcs_table_list` (
  `table_name` varchar(255) NOT NULL,
  `table_type` varchar(255) DEFAULT NULL,
  `group_name` varchar(255) DEFAULT '',
  `column` int(11) NOT NULL DEFAULT '0',
  `row` int(11) NOT NULL DEFAULT '0',
  `columnSpan` int(11) NOT NULL DEFAULT '0',
  `rowSpan` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`table_name`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of a_wcs_table_list
-- ----------------------------
INSERT INTO `a_wcs_table_list` VALUES ('s_equip_station_status', 'storage', 'S2', '1', '0', '1', '20');
INSERT INTO `a_wcs_table_list` VALUES ('s_storage_station_status', 'storage', 'S1', '0', '0', '1', '20');

-- ----------------------------
-- Table structure for kh_agv_data
-- ----------------------------
DROP TABLE IF EXISTS `kh_agv_data`;
CREATE TABLE `kh_agv_data` (
  `agv_id` int(11) NOT NULL,
  `pos_x` float(11,4) DEFAULT NULL,
  `pos_y` float(11,4) DEFAULT NULL,
  `pos_th` float(11,4) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `error_code` int(11) DEFAULT NULL,
  `battery_level` float(11,4) DEFAULT NULL,
  `agv_type` int(11) DEFAULT NULL,
  `is_online` int(11) DEFAULT NULL,
  `is_serving` int(11) DEFAULT NULL,
  `is_assigned` int(11) DEFAULT NULL,
  `ip` varchar(255) DEFAULT NULL,
  `at_node` int(11) DEFAULT NULL,
  `at_station` varchar(255) DEFAULT NULL,
  `station_error_x` float(11,4) DEFAULT NULL,
  `station_error_y` float(11,4) DEFAULT NULL,
  `station_error_th` float(11,4) DEFAULT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `action` int(11) DEFAULT NULL,
  PRIMARY KEY (`agv_id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_agv_data
-- ----------------------------
INSERT INTO `kh_agv_data` VALUES ('1', '-0.9507', '117.2620', '87.5302', '0', '0', '49.2000', '2', '1', '0', '0', '192.168.1.201', '17', 'None', '999.0000', '999.0000', '999.0000', '2021-09-02 14:02:08', '0');
INSERT INTO `kh_agv_data` VALUES ('44', '51.7039', '5.1718', '178.8180', '0', '0', '50.8000', '2', '0', '0', '0', '192.168.1.124', '805', 'P4', '-0.0061', '0.1438', '-1.1508', '2021-09-02 13:18:55', '0');
INSERT INTO `kh_agv_data` VALUES ('46', '22.4873', '76.7110', '179.7090', '0', '0', '18.4000', '2', '0', '0', '0', '192.168.1.126', '737', 'P2', '0.0033', '0.0010', '-0.2910', '2021-09-01 22:07:13', '0');
INSERT INTO `kh_agv_data` VALUES ('51', '51.5100', '5.1800', '180.0000', '0', '0', '98.5546', '1', '1', '0', '1', '127.0.0.1', '805', 'P4', '0.0040', '0.0020', '0.0329', '2021-09-22 16:44:01', '0');
INSERT INTO `kh_agv_data` VALUES ('52', '21.5100', '5.7800', '-179.8340', '0', '0', '100.0000', '1', '1', '0', '0', '127.0.0.1', '798', 'P3', '0.0000', '0.0050', '-359.8340', '2021-09-22 16:44:01', '0');
INSERT INTO `kh_agv_data` VALUES ('53', '52.4900', '60.8530', '-179.9630', '2', '7', '99.9992', '2', '0', '0', '1', '127.0.0.1', '721', 'P1', '0.0000', '0.0000', '-359.9630', '2021-08-31 10:58:36', '0');
INSERT INTO `kh_agv_data` VALUES ('54', '-29.1000', '1.2500', '0.0000', '0', '0', '100.0000', '2', '1', '0', '0', '127.0.0.1', '60', 'P4', '0.0000', '0.0000', '0.0000', '2021-04-17 14:50:10', '0');
INSERT INTO `kh_agv_data` VALUES ('61', '38.8550', '-6.3780', '180.0000', '0', '0', '89.3433', '2', '1', '0', '0', '127.0.0.1', '770', 'F9WC-11-2-G-W', '0.0000', '0.0000', '180.0000', '2021-09-01 19:50:14', '0');
INSERT INTO `kh_agv_data` VALUES ('62', '-44.9170', '4.4340', '0.0000', '0', '0', '61.4403', '2', '1', '0', '0', '127.0.0.1', '292', 'F9WC-9-1-P-W', '0.0000', '0.0000', '-180.0000', '2021-09-01 19:50:14', '0');
INSERT INTO `kh_agv_data` VALUES ('63', '29.6620', '86.7000', '-90.0000', '0', '0', '87.3975', '2', '1', '0', '0', '127.0.0.1', '133', 'B16', '0.0000', '0.0000', '0.0000', '2021-09-01 19:50:14', '0');
INSERT INTO `kh_agv_data` VALUES ('64', '28.6200', '81.1400', '0.0000', '0', '0', '72.4464', '2', '1', '0', '0', '127.0.0.1', '451', 'F9WC-4-G-W', '0.0000', '0.0000', '-180.0000', '2021-09-01 19:50:14', '0');
INSERT INTO `kh_agv_data` VALUES ('65', '-40.0000', '86.6000', '-90.0000', '0', '0', '81.9737', '2', '1', '0', '0', '127.0.0.1', '178', 'D1', '0.0000', '0.0000', '0.0000', '2021-09-01 19:50:14', '0');

-- ----------------------------
-- Table structure for kh_equipment_info
-- ----------------------------
DROP TABLE IF EXISTS `kh_equipment_info`;
CREATE TABLE `kh_equipment_info` (
  `ID` int(11) NOT NULL,
  `EQUIP_ID` varchar(255) NOT NULL,
  `EQUIP_STATUS` varchar(255) NOT NULL,
  `STATUS` varchar(255) DEFAULT NULL,
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_equipment_info
-- ----------------------------

-- ----------------------------
-- Table structure for kh_order_info
-- ----------------------------
DROP TABLE IF EXISTS `kh_order_info`;
CREATE TABLE `kh_order_info` (
  `ORDER_ID` varchar(255) NOT NULL DEFAULT '',
  `START` varchar(255) NOT NULL DEFAULT '',
  `TARGET` varchar(255) NOT NULL DEFAULT '',
  `PRIORITY` int(11) NOT NULL DEFAULT '1',
  `STATUS` varchar(255) NOT NULL DEFAULT '',
  `MODE` varchar(255) NOT NULL DEFAULT '',
  `TYPE` varchar(255) NOT NULL DEFAULT '',
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `AGV_ID` int(11) DEFAULT '-1' COMMENT '默认-1',
  `PALLETNO` varchar(255) DEFAULT '',
  PRIMARY KEY (`ORDER_ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='BEGIN\r\n		DECLARE storage_is_open INT(11);\r\n    IF(NEW.`STATUS` = ''NEW'')\r\n    THEN\r\n\r\n        SET storage_is_open=(SELECT COUNT(*) FROM s_equip_station_status WHERE storage_name=NEW.`START` AND storage_status="FULL");\r\n				IF(storage_is_open = 0)\r\n				THEN\r\n					SET NEW.`STATUS`="ERR";\r\n				END IF;\r\n    END IF;\r\nEND';

-- ----------------------------
-- Records of kh_order_info
-- ----------------------------

-- ----------------------------
-- Table structure for kh_order_info_copy1
-- ----------------------------
DROP TABLE IF EXISTS `kh_order_info_copy1`;
CREATE TABLE `kh_order_info_copy1` (
  `ORDER_ID` varchar(255) NOT NULL DEFAULT '',
  `START` varchar(255) NOT NULL DEFAULT '',
  `TARGET` varchar(255) NOT NULL DEFAULT '',
  `PRIORITY` int(11) NOT NULL DEFAULT '1',
  `STATUS` varchar(255) NOT NULL DEFAULT '',
  `MODE` varchar(255) NOT NULL DEFAULT '',
  `TYPE` varchar(255) NOT NULL DEFAULT '',
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `AGV_ID` int(11) DEFAULT '-1' COMMENT '默认-1',
  `PALLETNO` varchar(255) DEFAULT '',
  PRIMARY KEY (`ORDER_ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='BEGIN\r\n		DECLARE storage_is_open INT(11);\r\n    IF(NEW.`STATUS` = ''NEW'')\r\n    THEN\r\n\r\n        SET storage_is_open=(SELECT COUNT(*) FROM s_equip_station_status WHERE storage_name=NEW.`START` AND storage_status="FULL");\r\n				IF(storage_is_open = 0)\r\n				THEN\r\n					SET NEW.`STATUS`="ERR";\r\n				END IF;\r\n    END IF;\r\nEND';

-- ----------------------------
-- Records of kh_order_info_copy1
-- ----------------------------
INSERT INTO `kh_order_info_copy1` VALUES ('0018c8de-1c79-43cf-9165-64c21f373a83', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 08:23:37', '-1', 'PAL21081507264');
INSERT INTO `kh_order_info_copy1` VALUES ('005859c5-058c-4323-ab32-855eb22266f9', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 14:14:23', '-1', 'PAL21081614559');
INSERT INTO `kh_order_info_copy1` VALUES ('007dbd94-a8a3-4a36-a981-7e6bee381952', 'F9WC-12-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 15:01:59', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('00a6feb8-caf4-4d82-8ce2-4802b2328e4c', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 17:38:54', '-1', 'PAL21081820414');
INSERT INTO `kh_order_info_copy1` VALUES ('00ab39af-fb68-4b3a-9ccf-a1a52ec05538', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 09:21:05', '-1', 'PAL21081808972');
INSERT INTO `kh_order_info_copy1` VALUES ('018d8971-960e-4f79-b643-47163d2c7335', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 07:08:36', '-1', 'PAL21081604661');
INSERT INTO `kh_order_info_copy1` VALUES ('01c3855f-e450-4b03-b9cd-cf56c196adb2', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 19:59:27', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('020aacb2-ebe3-4fed-a088-5fc9c5e3c92b', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 12:00:59', '-1', 'PAL21081811683');
INSERT INTO `kh_order_info_copy1` VALUES ('021ede98-00ff-469d-abe5-67c3e387f0c9', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 08:27:53', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('02a30324-8949-4f42-8908-14420f2714af', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:27:35', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('038017c8-b8c2-4f5f-aff0-699fa496bb38', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:19:32', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0389682a-a81d-4c6e-8bd5-abe03d1365e8', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:49:01', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('03a0789e-ca12-4cf8-b4a9-219f137083a6', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 10:49:45', '-1', 'PAL21081610805');
INSERT INTO `kh_order_info_copy1` VALUES ('03f033eb-4719-4a80-87bf-ba005e7ed8ea', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 19:41:59', '-1', 'PAL21081822712');
INSERT INTO `kh_order_info_copy1` VALUES ('03f3658f-6ac3-4bf0-8b6d-846501f36d70', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 12:10:52', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0405bc44-b917-4706-a167-e95bcbacded2', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 07:15:36', '-1', 'PAL21081805936');
INSERT INTO `kh_order_info_copy1` VALUES ('041ac74b-1337-4c6e-86c2-2def3fbf89fc', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 01:42:54', '-1', 'PAL21081600438');
INSERT INTO `kh_order_info_copy1` VALUES ('041db352-832b-4fce-a5c2-2e3653effd0c', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:32:22', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('044b05de-f2d2-4661-aaa4-7184d2f01cfd', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 04:56:31', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0455836d-6e68-4fe6-b0ec-c519c2b76c0d', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:37:02', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('04625c41-8916-4fcc-9af7-cecdc18a0cf1', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 13:55:24', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0464a8aa-d6de-4a5c-b1ac-e8041ca7410b', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 11:38:29', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('047d5736-b5a2-4b3e-88a0-6a4e09c911d3', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 11:35:22', '-1', 'PAL21081610910');
INSERT INTO `kh_order_info_copy1` VALUES ('048fdf4f-7c50-4b8c-ab81-d2a2e58e99cc', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 08:42:28', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('04920615-0889-4ac2-aa58-25adbcde3aa5', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 16:07:57', '-1', 'PAL21081718543');
INSERT INTO `kh_order_info_copy1` VALUES ('04c0186c-8472-438f-8f6e-faaa7cec660a', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:03', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('04dd9731-fa08-4660-9cb1-ea415dcc7c23', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 18:29:13', '-1', 'PAL21081519215');
INSERT INTO `kh_order_info_copy1` VALUES ('04e80b4f-d957-4a5f-a07b-39dbeb3bc9f4', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 03:12:44', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('04eabd4e-69b4-4f2f-bd38-a129b851c35c', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 11:35:43', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('05050e6f-30d9-4afe-b756-34bd758a228a', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:06:33', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0567d3fb-8303-4dd8-a0f3-73e935ce7872', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 05:54:01', '-1', 'PAL21081504793');
INSERT INTO `kh_order_info_copy1` VALUES ('0581ed88-b421-4741-8af0-d95513f9c317', 'F9WC-12-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 23:24:22', '-1', 'PAL21081722534');
INSERT INTO `kh_order_info_copy1` VALUES ('05948938-3172-44aa-b14e-1a5f43848550', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 03:08:13', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('05ca9358-12c1-48b7-a0b9-47ae37f2a3cf', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 08:02:22', '-1', 'PAL21081807415');
INSERT INTO `kh_order_info_copy1` VALUES ('06293883-226f-4388-9a9c-e62d2b7f4dfc', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 20:16:22', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('063b0eba-ecbd-4072-aeca-0bc32b2d5a65', 'F9WC-12-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:51:24', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('06859f12-079a-4598-a50b-9a91afbc6668', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:33:54', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('06d0f249-6cb5-4b4f-817d-d26913cde89e', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 14:45:51', '-1', 'PAL21081815034');
INSERT INTO `kh_order_info_copy1` VALUES ('06e06ebe-766d-4088-b9ec-e19700a2211d', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:18:52', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('06e9f073-888a-497e-819b-bcb38d124df1', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:14:32', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('07067a73-4ddf-4fd4-b29d-100f582239c9', 'F9WC-3-1', '', '2', 'OVER', 'GOODS', 'CARRY', '2021-08-17 18:10:03', '-1', 'PAL21081717498');
INSERT INTO `kh_order_info_copy1` VALUES ('072e7783-b71c-4e74-9bc6-ee55db3041dc', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:57:15', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('074eab73-e10c-4749-8b5f-56ee03b4335d', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 20:51:29', '-1', 'PAL21081521231');
INSERT INTO `kh_order_info_copy1` VALUES ('0795031a-f4ed-490d-a66e-55c28f8e19fe', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 12:08:32', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('07afe30b-42cf-42ad-8dcb-dcd423bb14c0', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 06:24:20', '-1', 'PAL21081505123');
INSERT INTO `kh_order_info_copy1` VALUES ('081cf685-fb5e-4f17-8fe0-b02bfb077c06', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 08:50:37', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('083b0d74-14b2-49cd-8626-3fb180c71fb6', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 07:18:16', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('08d10779-2637-4f74-a542-8b35cf08db2e', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 13:46:07', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('090782a5-59c1-4523-92c1-e32036e7afe4', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 05:01:19', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0928424e-8895-451b-9c77-2f8f2fa9c343', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 18:58:33', '-1', 'PAL21081419520');
INSERT INTO `kh_order_info_copy1` VALUES ('0a293df8-2d0f-4017-88f4-4a0b7278440d', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:31', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0a7f6a8c-13f2-472d-8870-f9bc25c9993f', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:33:32', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0b9d08d1-1256-4ea1-b5f0-27f12096238c', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 23:14:32', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0bc1716e-8341-4d71-812f-53983c8237b9', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:16:38', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0be7f22f-b8f4-4d97-9981-e7d384b7cf2f', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 01:00:50', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0bf9ce42-bf43-4224-ae78-c570b17e627d', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 01:15:00', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0cbcc47f-d1fd-4942-8747-5743a22aee93', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:43:28', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0cf09095-276b-4afb-b8ce-5a69e84dc76c', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 10:13:55', '-1', 'PAL21081710361');
INSERT INTO `kh_order_info_copy1` VALUES ('0d0f9f24-debe-468f-a370-0d13a0ee32b7', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:39:11', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0d453efd-8a3e-406b-8702-321b26e7d966', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 21:17:31', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0e055f50-3ae3-4da0-a16f-dee55b3df2e2', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 06:38:34', '-1', 'PAL21081705670');
INSERT INTO `kh_order_info_copy1` VALUES ('0e240dff-b740-41b8-9d81-acc4c62342d7', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:08:56', '-1', 'PAL21081905891');
INSERT INTO `kh_order_info_copy1` VALUES ('0e934823-a676-4515-b539-39788dbd44dd', 'F9WC-12-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:16:23', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0e93f36b-da23-4e10-857e-7fc0f6fce519', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 21:13:39', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0f0b4cca-dbd3-4675-893b-ab3828f260d8', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 03:23:46', '-1', 'PAL21081502055');
INSERT INTO `kh_order_info_copy1` VALUES ('0f22bf5f-0549-4ff3-a1f1-39f62dcffb80', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 23:14:32', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0f406234-4bb7-425c-83a3-0b8e1f350199', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 12:00:29', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0f40a44b-974d-48d6-a01a-14302c551143', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 07:10:01', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0f799ab2-ea07-4fcb-8ac3-13b6f49940c5', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 01:15:56', '-1', 'PAL21081827299');
INSERT INTO `kh_order_info_copy1` VALUES ('0f8bb046-a6a0-4add-88cb-6e7b924aa005', 'F9WC-13-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 13:16:38', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0fb815a3-f837-4da9-ad13-9dd0190840cf', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:01:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0fc3f83e-7799-48c5-8d81-b80f5b990d75', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 15:32:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('0fc63be5-585c-4d83-b2b6-700b08868424', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 21:13:05', '-1', 'PAL21081822084');
INSERT INTO `kh_order_info_copy1` VALUES ('0fd11589-c126-4e9f-a50e-1c07b50fabe8', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 12:31:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('100181bc-a8ce-4b92-babf-e6ea6d0d3c85', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 17:50:48', '-1', 'PAL21081819392');
INSERT INTO `kh_order_info_copy1` VALUES ('10751ed6-8577-407e-b4b0-e0a5ab8394c3', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 01:20:51', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1078a0a7-e841-4d22-b50f-97ededd4da77', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:31:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('107c1158-df1d-4a74-a1db-3da5df1b9cbc', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 01:20:25', '-1', 'PAL21081526782');
INSERT INTO `kh_order_info_copy1` VALUES ('111ba60b-853c-44dc-b573-46c843def10f', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 10:59:27', '-1', 'PAL21081509978');
INSERT INTO `kh_order_info_copy1` VALUES ('114c5c5c-ffba-4126-9b1e-ea02cdb539ec', 'F9WC-12-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:47:22', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('11adb00d-bd31-4dcb-87db-a32763bde526', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 03:19:30', '-1', 'PAL21081801800');
INSERT INTO `kh_order_info_copy1` VALUES ('12493d7c-486b-4f2f-a56b-feb48cf452b3', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 12:27:12', '-1', 'PAL21081610507');
INSERT INTO `kh_order_info_copy1` VALUES ('125bf0ff-afe9-4246-8959-51c0908bb921', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 15:53:35', '-1', 'PAL21081815911');
INSERT INTO `kh_order_info_copy1` VALUES ('1266fec6-87a3-48f4-b57d-ec16dc8635c2', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 03:14:24', '-1', 'PAL21081802553');
INSERT INTO `kh_order_info_copy1` VALUES ('12739cdb-66a9-45b9-99d7-d90756d472fb', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-15 01:32:12', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('12fe6f3a-2530-478b-afc9-22b6fd53d8f7', 'F9WC-1-2', '', '2', 'OVER', 'GOODS', 'CARRY', '2021-08-19 17:49:03', '-1', 'PAL21081917104');
INSERT INTO `kh_order_info_copy1` VALUES ('13095c6a-d1c8-40b3-8d89-22940a6f01b1', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 22:07:56', '-1', 'PAL21081523442');
INSERT INTO `kh_order_info_copy1` VALUES ('137afba9-da2f-4af1-affb-10c842de3e78', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 23:14:32', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('13abc5a7-e171-466c-bb31-88386702614b', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 01:35:52', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('143f73a6-32eb-4161-8ec7-a4f8119e0937', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 12:27:12', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('14534859-c503-44f3-a942-d1e0436e8adf', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 20:45:43', '-1', 'PAL21081723835');
INSERT INTO `kh_order_info_copy1` VALUES ('1487c589-b337-4b6e-a120-d83d09e66e6c', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:42:57', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('149088a3-ec87-4a06-80f9-e8d334346e55', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 20:31:37', '-1', 'PAL21081422944');
INSERT INTO `kh_order_info_copy1` VALUES ('151a3a1a-3988-4935-87e5-1e00539e48f2', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 09:06:17', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('151e903b-5ae0-4ea3-8ca1-440a4b19c5be', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 00:38:53', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('15785819-7c26-4757-bcba-f30598454ff9', 'F9WC-1-2', '', '2', 'OVER', 'GOODS', 'CARRY', '2021-08-18 23:51:06', '-1', 'PAL21081825233');
INSERT INTO `kh_order_info_copy1` VALUES ('15af1f78-3b29-4edf-9413-36d59e44e355', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 12:00:27', '-1', 'PAL21081611653');
INSERT INTO `kh_order_info_copy1` VALUES ('15fa868c-9c01-4308-8afc-e533d79de010', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 05:56:43', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1609a8fb-a6e9-4e30-afe3-0f6bd0e85d35', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 02:50:03', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('163eaa17-6b43-4147-90c1-1098cec9f613', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 21:15:06', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1740169e-7b9a-4281-9438-a65acd228819', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 12:33:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('179ad26e-494d-483e-b41f-d23026d9f82c', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 21:55:02', '-1', 'PAL21081520846');
INSERT INTO `kh_order_info_copy1` VALUES ('17bf95ad-813d-4dba-8c91-8e0a3eaea724', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 04:31:48', '-1', 'PAL21081503090');
INSERT INTO `kh_order_info_copy1` VALUES ('17de3310-486c-4485-baf4-9f92e92cb267', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:26:16', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1829432c-5f35-4eb9-9a64-d51e3ef08397', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 09:13:13', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('18496ce6-9974-4b1a-8556-21d61acf2b11', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 08:29:39', '-1', 'PAL21081607622');
INSERT INTO `kh_order_info_copy1` VALUES ('188c1468-5702-4722-99dc-53e027cdf274', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 03:46:39', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('19090f1f-80d4-4d6a-b6c3-f9e24145dbc7', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:19:17', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('19627e78-cd45-4f92-ad56-2474b2834bf0', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:23:39', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('19911609-a276-4b01-be0a-4a5c57c34c6c', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 23:20:27', '-1', 'PAL21081624331');
INSERT INTO `kh_order_info_copy1` VALUES ('1999904b-296c-4f98-93a3-8ecc44a5c07e', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 03:14:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1a1fa19d-a7cd-4630-b0f4-1b042a1d5771', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 11:09:32', '-1', 'PAL21081912138');
INSERT INTO `kh_order_info_copy1` VALUES ('1acd9e1c-08cc-4a79-85ea-f8960df5397e', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 01:14:16', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1ae24836-e5e2-47f5-96b3-d16f913b9f86', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 05:09:41', '-1', 'PAL21081503746');
INSERT INTO `kh_order_info_copy1` VALUES ('1af38143-0f6f-4e11-8e33-f7bbfe432c59', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 12:01:10', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1b735d42-bf43-408f-a5ba-b116f822ecf1', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 07:23:53', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1b771ff1-4277-456b-adb9-17f5680d0152', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 21:29:29', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1c2007fa-f4f3-4c89-86d6-41cc05d30478', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 09:38:49', '-1', 'PAL21081609381');
INSERT INTO `kh_order_info_copy1` VALUES ('1c3c4bdf-f7fb-4da2-8bfa-1a0c325eb6cc', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 14:19:35', '-1', 'PAL21081914270');
INSERT INTO `kh_order_info_copy1` VALUES ('1c5aeb8f-85aa-45c3-896f-1dbdb1334ad2', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 05:20:51', '-1', 'PAL21081804527');
INSERT INTO `kh_order_info_copy1` VALUES ('1c837ee0-2dd3-4fbf-ac12-31c16b8ee8c7', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:57:17', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1cb7430b-f422-4847-989c-13b62864f1bb', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 13:33:04', '-1', 'PAL21081713395');
INSERT INTO `kh_order_info_copy1` VALUES ('1cc407b5-ffda-446e-a643-bdfe02739694', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 03:12:40', '-1', 'PAL21081601885');
INSERT INTO `kh_order_info_copy1` VALUES ('1db4f6f7-2fc6-4387-98ea-99439408778e', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 17:57:13', '-1', 'PAL21081618613');
INSERT INTO `kh_order_info_copy1` VALUES ('1e669c21-8354-4c44-87dc-e5268eba6e48', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:40:30', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1ec758c7-f625-4502-ba12-d937e355762f', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1ed40e4f-83eb-4570-b2d8-227c28dc8b44', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 04:55:30', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1edeaa34-fbbb-4d36-be9c-8635982e878c', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:17:56', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('1f8ce22e-4d10-4b72-b190-46c82e2debc7', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 14:43:05', '-1', 'PAL21081515005');
INSERT INTO `kh_order_info_copy1` VALUES ('1fb1b841-57b1-4467-b39d-3d618b688fc2', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 10:33:54', '-1', 'PAL21081511715');
INSERT INTO `kh_order_info_copy1` VALUES ('1ffeba5e-a2b4-430a-973d-40ac73b96593', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 17:36:58', '-1', 'PAL21081517744');
INSERT INTO `kh_order_info_copy1` VALUES ('201937cb-bfce-4fde-af0d-4ed16a59687d', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 08:42:59', '-1', 'PAL21081604354');
INSERT INTO `kh_order_info_copy1` VALUES ('2074f186-c15e-4f5c-bf4c-c6b18c6ce97a', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 19:51:55', '-1', 'PAL21081420670');
INSERT INTO `kh_order_info_copy1` VALUES ('20f6eb62-31c8-41a8-8490-ac93debdbd93', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:33:06', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2107eb20-ecf0-4b32-bdeb-d7c14096bcb2', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 06:41:32', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('211a6b5f-932f-46af-ac16-3d1ca279d88f', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:02:22', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('21887afa-2af3-4068-a677-d77a6d945f5d', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:04:29', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('229ee1d9-561b-45d6-80ca-739de1c3740c', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 10:46:13', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('22b0b6b6-4854-4719-915b-82d3e33b7321', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:16:16', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('22df5639-8e60-492e-a5fa-818333f5607a', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 06:30:59', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('22edf93e-7175-401a-b964-aa68fe4e90ee', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:19:59', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('230a12e8-52af-4bff-a845-7f18534d4b64', 'F9WC-12-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 04:37:30', '-1', 'PAL21081800988');
INSERT INTO `kh_order_info_copy1` VALUES ('232c5c2b-0aeb-4fee-bf52-1ff8096bf2d2', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 22:27:08', '-1', 'PAL21081622888');
INSERT INTO `kh_order_info_copy1` VALUES ('23d996f2-111d-477f-8851-0f143a5aafe3', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 00:22:38', '-1', 'PAL21081525617');
INSERT INTO `kh_order_info_copy1` VALUES ('241e5764-22bf-446a-9219-8c16be743fb6', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 00:21:08', '-1', 'PAL21081826454');
INSERT INTO `kh_order_info_copy1` VALUES ('241ee410-6ac2-4863-84d3-509d7c058a8d', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 01:10:07', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2454ff7e-d9cb-4b6d-a745-3f044a8689ca', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 14:58:50', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('24ce9a07-322e-45ed-94f8-438f8148502c', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:05:01', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('24ea5d01-6ed2-477b-97f5-5aaf2c4c88c6', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:17:55', '-1', 'PAL21081424949');
INSERT INTO `kh_order_info_copy1` VALUES ('252d2e52-9998-412c-b7e3-16f40a1006b1', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:23:48', '-1', 'PAL21081908139');
INSERT INTO `kh_order_info_copy1` VALUES ('25671d9d-ec0c-4a07-b785-23757099132b', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 14:54:09', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('258006f1-2af7-4e0a-996e-ba86c5f05fff', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 14:04:03', '-1', 'PAL21081713821');
INSERT INTO `kh_order_info_copy1` VALUES ('25abcecb-0051-4c33-99c7-2364be131080', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:12:55', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('25e529a9-4e1b-4a08-a764-18792ad91d10', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 04:41:41', '-1', 'PAL21081802797');
INSERT INTO `kh_order_info_copy1` VALUES ('26180659-4aff-4088-bb83-0cb97e3324ea', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 01:56:35', '-1', 'PAL21081802161');
INSERT INTO `kh_order_info_copy1` VALUES ('262407f1-28f6-4ece-aa39-2c1a5f7167d0', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 16:10:05', '-1', 'PAL21081816506');
INSERT INTO `kh_order_info_copy1` VALUES ('26900c16-30a4-46ff-bea4-02154b52af5e', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 15:02:31', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2696565c-00eb-4d1f-b0a6-98c7a980c8eb', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 03:56:38', '-1', 'PAL21081502534');
INSERT INTO `kh_order_info_copy1` VALUES ('2699f754-00cf-49c3-a24d-f44eab04fbac', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 18:34:01', '-1', 'PAL21081420642');
INSERT INTO `kh_order_info_copy1` VALUES ('26ec4b6d-4bfd-4d5c-bf52-806b07a0a68e', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 13:01:26', '-1', 'PAL21081911983');
INSERT INTO `kh_order_info_copy1` VALUES ('275f7208-bf73-4524-9a5d-478cb06e9f1a', 'F9WC-13-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 16:41:01', '-1', 'PAL21081515397');
INSERT INTO `kh_order_info_copy1` VALUES ('27785a4c-6513-4906-ad7a-60047c748313', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 17:09:03', '-1', 'PAL21081717401');
INSERT INTO `kh_order_info_copy1` VALUES ('28179041-a07a-459c-94c0-3fe8e87d94da', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:17:55', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('28e13560-f299-4081-8a53-6132146c230c', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:09:53', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('290fc6ad-05b9-4ff8-9c0a-1e3ad6fa2bfc', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:29', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2934e6bb-975f-4a4f-a410-7b80bcc1ae2e', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 12:04:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('29621f51-aa81-4607-82f4-f63b3f62d0cf', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 02:17:56', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('29884917-4ecf-4d48-bcf9-d7ace1c3ee62', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 02:36:59', '-1', 'PAL21081502836');
INSERT INTO `kh_order_info_copy1` VALUES ('299d599c-db7f-42ce-987a-5854efdf05bd', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-16 20:27:40', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('29d55565-9148-4982-8947-811e955f705d', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:47:15', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2a2153f1-627e-41aa-91db-e358da702388', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 13:16:35', '-1', 'PAL21081914373');
INSERT INTO `kh_order_info_copy1` VALUES ('2a6ae7a6-ff50-4363-978b-1399aba47765', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:11:38', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2a84060e-36c6-42ef-bf63-a4117a22b45a', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 06:53:49', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2a910ccb-b2f8-406a-b7e1-0c4cfbab3b08', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 04:54:01', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2adba3c0-3ff3-4f87-b1ce-b462ad112569', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 11:10:44', '-1', 'PAL21081510194');
INSERT INTO `kh_order_info_copy1` VALUES ('2aecc671-18fa-40d8-b7af-afb89e990820', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:10:03', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2b46137c-0345-4b31-9d6e-edb8655cf14b', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 08:14:23', '-1', 'PAL21081707802');
INSERT INTO `kh_order_info_copy1` VALUES ('2bba662e-2611-4d09-be62-f40843b9b43c', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 16:02:56', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2c206d63-83ae-41f1-91c2-6d69a73f84e4', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 17:29:21', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2c269e0c-4a32-4cf1-bd94-9ac9bfe92f18', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:18:47', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2c320aad-3cd7-439c-a1dd-8f8f5a9f1008', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 18:02:06', '-1', 'PAL21081718182');
INSERT INTO `kh_order_info_copy1` VALUES ('2c782a8c-955f-4191-9c32-ee46d9819fc0', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 08:02:28', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2cbbddf4-7f4d-4d42-9c1d-3d33591ed237', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:56:47', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2ccebf1f-15df-457f-a08b-3ac79bc20be8', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 18:26:13', '-1', 'PAL21081526731');
INSERT INTO `kh_order_info_copy1` VALUES ('2d1a238e-e9b5-4b49-b3ca-24f54af49170', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:17:56', '-1', 'PAL21081424931');
INSERT INTO `kh_order_info_copy1` VALUES ('2d346349-11ad-43e9-bf84-2f1e8e6dbc5c', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 21:14:29', '-1', 'PAL21081822855');
INSERT INTO `kh_order_info_copy1` VALUES ('2d3a63c0-ee7a-486d-84bf-c514a98fee62', 'F9WC-13-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 11:50:59', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2d44e187-2685-4617-9eb1-7d0140154bf4', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 08:30:46', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2d5153e7-2dc4-4445-bb85-5713c8359713', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 03:35:35', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2d73218a-ea82-47ef-8c60-0cd4f14a5d38', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 19:46:04', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2d9d936c-8438-4fbb-a5c5-370b0d3e2e48', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 10:31:31', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2dc0ba8b-5bf4-4b51-95fb-b4ac4a0c3e60', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 09:50:14', '-1', 'PAL21081809767');
INSERT INTO `kh_order_info_copy1` VALUES ('2e563dcd-8f29-4ea2-839c-8f71e326064d', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 12:28:27', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2e599b93-b784-40ba-b80a-6e52d871e3d2', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 08:09:11', '-1', 'PAL21081707369');
INSERT INTO `kh_order_info_copy1` VALUES ('2ef63c65-a5bf-4d07-b20a-df37d3636e11', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 23:20:30', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2f0db74d-0711-4b52-befe-fb1481e0a4a6', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 01:30:07', '-1', 'PAL21081425959');
INSERT INTO `kh_order_info_copy1` VALUES ('2f1b95c6-b7df-42cb-b85a-6ab245bc7ac9', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 21:49:08', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2f5e5302-8e75-4348-8f95-9e4d26c279a4', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2f796fe7-ae52-4a36-81d5-d3b79cc1ff14', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 11:51:58', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2f8ae1ba-f70d-41f2-bf26-93c5b4b1ed57', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 11:49:52', '-1', 'PAL21081813713');
INSERT INTO `kh_order_info_copy1` VALUES ('2f999b8e-502c-43bd-9e7b-2cb3b1545db8', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 04:12:25', '-1', 'PAL21081702619');
INSERT INTO `kh_order_info_copy1` VALUES ('2fc026e8-1798-42c6-850a-4cc6bd4dbc5a', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 10:39:39', '-1', 'PAL21081810562');
INSERT INTO `kh_order_info_copy1` VALUES ('2fdbc9af-3a87-4374-8192-a0dfb259d8bc', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:16:03', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('2ff10efb-0225-4da5-a107-f43ea762ea44', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:02:18', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('30131e9e-4f7f-4e4d-a774-a9a5150a9595', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 06:23:08', '-1', 'PAL21081605192');
INSERT INTO `kh_order_info_copy1` VALUES ('3019d7d1-63d1-4eaa-b33f-2b26a6c17926', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 16:23:04', '-1', 'PAL21081817374');
INSERT INTO `kh_order_info_copy1` VALUES ('302b71ce-b557-4834-b71b-3083e3f9231c', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 17:28:35', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('302cf03f-8034-4d7c-94e5-2d7ca89abc66', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 20:39:16', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('30947bb5-492f-49ea-a3ed-055cb9b1f794', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:52:48', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3113fd38-e6ed-4765-9ff9-3b48a8bc0cac', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:26:14', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('31234126-f6dd-458a-aa69-faf551f177ed', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 19:09:14', '-1', 'PAL21081419568');
INSERT INTO `kh_order_info_copy1` VALUES ('318dd5ec-9050-4bc6-9678-21bd82d597a7', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 19:52:53', '-1', 'PAL21081720666');
INSERT INTO `kh_order_info_copy1` VALUES ('31976ef0-b878-4abc-9558-9f7d5a3b8725', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:24:42', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('319aa989-14da-4390-b878-e30a0655257d', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 10:06:18', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('31b50c52-7eaa-43f5-accc-063343432545', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 17:36:15', '-1', 'PAL21081916833');
INSERT INTO `kh_order_info_copy1` VALUES ('31e06a20-2335-4cfb-8a95-aeb4003a5cc3', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:29', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('321232ce-add9-44a3-9171-5268c68fb91c', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 13:40:31', '-1', 'PAL21081812182');
INSERT INTO `kh_order_info_copy1` VALUES ('325f0f49-88bb-4bcb-8465-5eb15bb5d1d6', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:21:15', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('32802fa6-f14a-4c80-b7d0-94aa19816c43', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 04:00:07', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('33aca0fd-bf85-4293-ba66-2b40595aebf0', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 17:57:35', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('33b1d0b6-1b65-43d4-9649-194de0e7aed1', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 08:21:40', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('33c50d04-e15c-4249-8bd4-1f025aee6f94', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 16:32:05', '-1', 'PAL21081517047');
INSERT INTO `kh_order_info_copy1` VALUES ('33cb9da8-8073-46dc-8ee7-4febd77f1edc', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 14:48:34', '-1', 'PAL21081614293');
INSERT INTO `kh_order_info_copy1` VALUES ('33e39797-8b65-439a-bece-d7222d0a44cb', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 20:27:37', '-1', 'PAL21081620569');
INSERT INTO `kh_order_info_copy1` VALUES ('346e0e55-c3a8-49fe-9834-c6b9d84a2ec7', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 08:27:42', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3485b536-daa6-43a3-b79e-82dc1c15bada', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 06:22:31', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('34c8e307-12dd-4734-814b-b2aaa8e8f68f', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 00:36:10', '-1', 'PAL21081726823');
INSERT INTO `kh_order_info_copy1` VALUES ('3501b936-aaf9-494d-8546-d74c65092fda', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 20:31:39', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('353c5dff-52f8-4da4-80cc-e2ffaa1fc11b', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 14:48:39', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('35841669-f3f5-40df-b416-2608b5fd832c', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:18:39', '-1', 'PAL21081515218');
INSERT INTO `kh_order_info_copy1` VALUES ('35f90407-4936-47c2-a9e3-93498a7ac58f', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 01:33:36', '-1', 'PAL21081500053');
INSERT INTO `kh_order_info_copy1` VALUES ('36381e8c-16b5-4e25-abfa-b4bc7da8480f', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 12:13:03', '-1', 'PAL21081714014');
INSERT INTO `kh_order_info_copy1` VALUES ('36c67849-2569-4e6c-b320-c76c2e03909e', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 23:40:09', '-1', 'PAL21081825216');
INSERT INTO `kh_order_info_copy1` VALUES ('37055367-f481-48de-b10a-7089cdaff17c', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 00:33:16', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3762ac8a-6cd3-4c1b-8c83-b2e6eab09ae1', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 10:14:45', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3762cedd-53c2-49a0-b07c-b87797ede306', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 10:07:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('376ac0b7-369d-4c9f-99dd-bf4be9f8cfc3', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 14:23:59', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3829ffee-9e60-4450-9186-8c22e5d25d08', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:59:05', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('38e34acf-6d6d-42c9-9d77-8dc364e88b47', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 05:55:34', '-1', 'PAL21081705120');
INSERT INTO `kh_order_info_copy1` VALUES ('38f1e113-fc05-4857-9c67-268196271897', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 00:52:14', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3910c03d-5f7b-4c82-b1ca-c4d62ae496ad', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 16:19:08', '-1', 'PAL21081915579');
INSERT INTO `kh_order_info_copy1` VALUES ('39306b57-f6cf-4757-aeca-dd098270862a', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 08:30:48', '-1', 'PAL21081706313');
INSERT INTO `kh_order_info_copy1` VALUES ('398f55bd-6321-4651-92a8-23512d0d4b3c', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 14:49:28', '-1', 'PAL21081908192');
INSERT INTO `kh_order_info_copy1` VALUES ('39e1563a-2832-4c48-9322-04f1cefdd95f', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 08:21:44', '-1', 'PAL21081906999');
INSERT INTO `kh_order_info_copy1` VALUES ('3a19b430-2dc8-4510-adfd-1e25bcddfa19', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 06:18:54', '-1', 'PAL21081804944');
INSERT INTO `kh_order_info_copy1` VALUES ('3a2d5659-1117-4c41-8cf7-e4730a3e04ad', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 19:58:50', '-1', 'PAL21081720882');
INSERT INTO `kh_order_info_copy1` VALUES ('3af4b0e4-b047-40f3-be82-5bf3986f065d', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:03:58', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3b6035f6-d005-46af-a7e5-a08794e1f464', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:04:15', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3b74f584-f353-418f-b385-d8f8e8e0fc23', 'F9WC-12-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:04:26', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3c1170ae-491c-45df-b419-a849080041ca', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 06:39:41', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3c5048cb-b43b-4416-aa9c-51ba02ee5099', 'F9WC-13-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:29:45', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3c71d978-d152-4408-a8c0-a546e1a4c912', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:20:14', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3c85ecef-42a1-4abe-bede-3bb38983ccc0', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 01:32:08', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3c8cdf72-c55d-4230-8f84-0a2b63651b6a', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 11:56:05', '-1', 'PAL21081712364');
INSERT INTO `kh_order_info_copy1` VALUES ('3c955dd5-b520-4e23-96e3-f36485dd8f83', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 03:34:55', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3d2cdd97-df14-470d-9729-d965a2b1def2', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 11:09:43', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3d324eee-8e25-4251-9dd0-4f5407002969', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:46:05', '-1', 'PAL21081901061');
INSERT INTO `kh_order_info_copy1` VALUES ('3d540779-def7-4161-9c54-6377eb093bcb', 'F9WC-12-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:32:53', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3d7358c0-e4c3-40a0-9c26-e2e63ceda486', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 00:29:26', '-1', 'PAL21081726135');
INSERT INTO `kh_order_info_copy1` VALUES ('3e2d1084-3587-43b9-9fa8-b85e57e0c9d2', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 15:36:27', '-1', 'PAL21081818058');
INSERT INTO `kh_order_info_copy1` VALUES ('3e51dcfa-f6a6-40bc-bf37-824109d9c932', 'F9WC-12-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:25:02', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3e9143c8-7f99-4322-bc78-f8c211dc11bf', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 01:56:41', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3f2ff238-e78d-45b6-91fa-ec021d29471b', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 17:09:29', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3f34c7da-bd2c-4ad0-b867-f0763caa9610', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 18:29:37', '-1', 'PAL21081819312');
INSERT INTO `kh_order_info_copy1` VALUES ('3f4562e6-4f11-4846-a160-c26baf2b2c32', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 10:38:15', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3f8875bf-42dc-4603-b4d8-555eba4e39a3', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 18:00:33', '-1', 'PAL21081818471');
INSERT INTO `kh_order_info_copy1` VALUES ('3fc55495-1e77-4c0f-9b3e-f7935e810c7d', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 14:21:54', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('3ff4eb6c-f926-4d69-a6ed-00b4dc2e1649', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 15:12:08', '-1', 'PAL21081613485');
INSERT INTO `kh_order_info_copy1` VALUES ('4075bc71-b144-4397-93d7-e1996b912082', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 12:17:22', '-1', 'PAL21081511856');
INSERT INTO `kh_order_info_copy1` VALUES ('40e0c229-c857-4fa8-96ac-d428f471d9d8', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:30:38', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('413678e1-beca-47d4-b110-3c0f61213e34', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:13:30', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('416ce534-33ca-48cc-bea6-8fa28900b0e0', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 03:16:57', '-1', 'PAL21081801652');
INSERT INTO `kh_order_info_copy1` VALUES ('4174512c-5a65-4ba1-ad12-f09e5de57dcd', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 08:26:59', '-1', 'PAL21081807622');
INSERT INTO `kh_order_info_copy1` VALUES ('41da9822-b3c9-4775-b8f6-d6f1c14e1682', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 14:46:17', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('43591a40-dea7-4905-90d1-4e537caceac6', 'F9WC-13-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:12:13', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('43c9d050-138f-4f9e-b643-6e6874204ad6', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:50:12', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('43ca5860-dc74-4601-8abb-3f209ee4f76d', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 12:35:53', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('44539a7f-c91f-4c76-b4ae-0a345ebc9317', 'F9WC-12-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 01:36:17', '-1', 'PAL21081427048');
INSERT INTO `kh_order_info_copy1` VALUES ('4489b436-7ae4-4689-bef0-0022ab01ca5b', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 09:46:16', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('44b29ffd-48a5-44c5-9909-e0afbb51a5c6', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 02:49:32', '-1', 'PAL21081600748');
INSERT INTO `kh_order_info_copy1` VALUES ('44facadd-4f08-49d6-9ce9-cbdb2c814dc3', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 03:08:11', '-1', 'PAL21081801632');
INSERT INTO `kh_order_info_copy1` VALUES ('45321cc3-c1b5-4f55-b4da-f625548d39af', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 05:48:55', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4536a4d0-a5b8-49ca-852b-d050d113b2ca', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 21:13:35', '-1', 'PAL21081421909');
INSERT INTO `kh_order_info_copy1` VALUES ('4538c208-e1b4-47e1-ab37-3fa87a7b33f9', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 18:41:40', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('455566a4-a6cc-4076-839e-78261a82d0cf', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 14:57:18', '-1', 'PAL21081913724');
INSERT INTO `kh_order_info_copy1` VALUES ('45582dbb-7e01-477e-966b-3160905b50bf', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 04:21:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('45b5e68c-4e5c-4ffc-9510-2773cac07cd1', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 08:57:16', '-1', 'PAL21081608822');
INSERT INTO `kh_order_info_copy1` VALUES ('45c1e940-fc35-4488-8a38-eadfedc8fd62', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:42:59', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('45c4ca08-70ea-462a-97be-29982d40a49d', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 10:31:54', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('45f7fc94-8fa6-4fc2-a1e5-2d08e3cdff8c', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 01:31:40', '-1', 'PAL21081727536');
INSERT INTO `kh_order_info_copy1` VALUES ('4606f901-c8a3-43c3-96ab-3e837f4ee129', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 10:07:17', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('460d2723-b230-4fc0-a01b-a79a70e439ff', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 19:59:23', '-1', 'PAL21081618809');
INSERT INTO `kh_order_info_copy1` VALUES ('460f2d6f-079b-48a0-9eee-a3fd803a6ea0', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 03:43:59', '-1', 'PAL21081902271');
INSERT INTO `kh_order_info_copy1` VALUES ('46ffed45-a856-4421-9935-443898abc3a5', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 05:38:16', '-1', 'PAL21081804376');
INSERT INTO `kh_order_info_copy1` VALUES ('4754d061-3520-4e53-bb62-adf9f799e49b', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:52:36', '-1', 'PAL21081425685');
INSERT INTO `kh_order_info_copy1` VALUES ('47757782-419a-498e-a7b7-e6d52414b0e8', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:43:43', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('477fc156-7fc2-4976-b398-c7c1af6ff6a1', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 21:29:25', '-1', 'PAL21081722537');
INSERT INTO `kh_order_info_copy1` VALUES ('47832232-dd75-497f-9c22-35672850c2e5', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:02:47', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('478cbd78-b003-4c50-8d59-0242cfdc167a', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:18:37', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('47909152-e789-47d8-8f81-482ced6b3e13', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:19:31', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('47dddb48-3090-4a17-b43b-c81c15a24cfd', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 16:02:53', '-1', 'PAL21081715984');
INSERT INTO `kh_order_info_copy1` VALUES ('47e03380-e99a-4141-9b4b-ceecd255c4b6', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 14:33:35', '-1', 'PAL21081814961');
INSERT INTO `kh_order_info_copy1` VALUES ('47e0ea78-238a-42b1-a49c-4b1d4d0eda8f', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 03:51:45', '-1', 'PAL21081502604');
INSERT INTO `kh_order_info_copy1` VALUES ('48305175-5ff1-43ea-8faa-179c373a6caf', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 07:07:07', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('48598f53-afd7-42e5-a39e-854284607946', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 21:43:03', '-1', 'PAL21081422147');
INSERT INTO `kh_order_info_copy1` VALUES ('486729fe-51af-448f-9e01-53949d3c3f70', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 07:07:05', '-1', 'PAL21081605903');
INSERT INTO `kh_order_info_copy1` VALUES ('48775afd-f5f8-4978-bd98-f46e27a7da29', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 18:06:15', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('48a404c8-5d60-4638-8c63-705ae7f2aac3', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 04:07:20', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('48a6b80c-bf23-4365-b4c9-653a0ca4f2a2', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 13:42:33', '-1', 'PAL21081912959');
INSERT INTO `kh_order_info_copy1` VALUES ('48d3d184-6dfe-41c4-b878-1cfcd93354e9', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:46:39', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('48d44e2a-b76a-45d7-8e03-f21fde65ceb2', 'F9WC-12-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:19:24', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('48eec6be-41e0-4690-af09-7a445e64f173', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 08:23:50', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('48f895c1-0f31-438d-94c4-54142c9a83f2', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:27:22', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('49186fa9-fd1f-4163-b5d1-f35d442fee17', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 15:40:59', '-1', 'PAL21081915001');
INSERT INTO `kh_order_info_copy1` VALUES ('49429cba-aac9-49bc-97fd-f71a75b19fec', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 23:51:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('49b1211d-0825-4950-8641-5040c8f22103', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 01:55:18', '-1', 'PAL21081602135');
INSERT INTO `kh_order_info_copy1` VALUES ('4a9818d1-c84b-4343-8b33-3e6b22febb03', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 17:12:22', '-1', 'PAL21081619073');
INSERT INTO `kh_order_info_copy1` VALUES ('4ab65a21-7393-436d-b3ed-23502d86dc10', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 07:30:13', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4abe9688-d5fe-4c79-8375-5af23a929f0e', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 11:16:28', '-1', 'PAL21081810559');
INSERT INTO `kh_order_info_copy1` VALUES ('4b331e76-948b-406c-85ea-649160f0fa1a', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 08:25:37', '-1', 'PAL21081709746');
INSERT INTO `kh_order_info_copy1` VALUES ('4b5cc1ca-3283-4391-bdfd-fd98293dd595', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 00:51:18', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4c41868a-4426-45cc-8f9c-b23c123b250a', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 19:59:14', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4c685738-43f7-4034-b659-c3d5a01a47b8', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 18:40:20', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4cd36071-1f61-4639-bd6b-f2906061790b', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:50:23', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4d58f99d-2e07-4cad-a7f6-5b82e8584141', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:05:17', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4d9dd1a9-cc1b-46f1-89dd-c2cca02d9e90', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 09:46:13', '-1', 'PAL21081608844');
INSERT INTO `kh_order_info_copy1` VALUES ('4db5df07-9916-47ba-8c52-1a5006c08fbe', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 06:18:45', '-1', 'PAL21081805051');
INSERT INTO `kh_order_info_copy1` VALUES ('4dbaa84e-194d-433e-b0b8-9eb05f076580', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:10:40', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4dcf000e-ce29-41f7-ace2-0a3f89fb0007', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 11:26:35', '-1', 'PAL21081612805');
INSERT INTO `kh_order_info_copy1` VALUES ('4e068a5f-1bb8-42ad-b377-a7f7dd47c5e1', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:30', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4e268301-9d8d-4229-8abc-2ec4be4cb283', 'F9WC-13-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 22:37:48', '-1', 'PAL21081823177');
INSERT INTO `kh_order_info_copy1` VALUES ('4e797e36-ea62-4fe8-a9c5-000f09ad9970', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 22:51:26', '-1', 'PAL21081824094');
INSERT INTO `kh_order_info_copy1` VALUES ('4e9a1508-16d4-4899-b08d-82edcd246929', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 04:54:23', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4ec0503b-ced6-4780-b33d-85ecfb66532e', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 23:45:58', '-1', 'PAL21081827406');
INSERT INTO `kh_order_info_copy1` VALUES ('4eee807d-912f-4b82-a50b-c2948e61278b', 'F9WC-13-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 19:15:02', '-1', 'PAL21081819154');
INSERT INTO `kh_order_info_copy1` VALUES ('4f301b3a-1db8-41ad-9735-09e6f3a66611', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:36:18', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4f4ff6f4-176a-4430-96dd-4a1197e7cb2f', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 18:29:51', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4f55ce78-cda7-429a-a88d-261079dc6128', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 20:03:31', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('4f717918-f894-4ccf-b2a1-b7ddece95966', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 03:50:30', '-1', 'PAL21081626421');
INSERT INTO `kh_order_info_copy1` VALUES ('50454c69-2067-4a94-bded-a2eed44be829', 'F9WC-12-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:24:20', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('504fe6ca-8737-47f1-84a6-5512aaeb9340', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 09:13:50', '-1', 'PAL21081808438');
INSERT INTO `kh_order_info_copy1` VALUES ('507e0b51-5f6f-4423-b65f-2546e06552fc', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:43:41', '-1', 'PAL21081906493');
INSERT INTO `kh_order_info_copy1` VALUES ('5086afe2-d1bb-46f1-a220-8c813eca6e64', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 15:20:17', '-1', 'PAL21081617101');
INSERT INTO `kh_order_info_copy1` VALUES ('50aa6635-9230-46e3-8775-6683f84fdb58', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:47:42', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('510f4b01-4f43-47e4-bd8d-42a13fc76b8a', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:04:10', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('51b5dcff-23fa-4dcf-b47a-805185d92db5', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 03:07:49', '62', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5202d038-0410-4c09-adae-8b297eabfab4', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 19:43:27', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('526dd6ae-4e00-4569-b603-169790e27e64', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:42:59', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('527b82c3-6e7d-4355-97b5-bb138685ec28', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 08:38:58', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('527c95d0-0cd0-4efe-81fc-150ff539e0e4', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 00:22:49', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('527e3ce4-e420-40d1-a284-1b819692f003', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:10:49', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('52e778d7-62d7-40f0-b185-055a5238850d', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 06:26:17', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('52ea18d1-56ce-4596-af1e-828de9a76a47', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:27:44', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('53137be1-c738-44eb-bc9b-eaf4d3b75dad', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:05:25', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('533ee5b1-afa3-459a-b252-45488a661868', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 15:32:35', '-1', 'PAL21081614980');
INSERT INTO `kh_order_info_copy1` VALUES ('5386f6ce-cd30-4e63-b269-29e2b55aa7d5', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 22:34:00', '-1', 'PAL21081425298');
INSERT INTO `kh_order_info_copy1` VALUES ('538a061b-b103-4b1e-91e6-6bf2007fd5b5', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 12:35:51', '-1', 'PAL21081612050');
INSERT INTO `kh_order_info_copy1` VALUES ('53cd1993-a9ab-4307-855c-d7aa882245b6', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:21:36', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('53e68f02-04a1-4305-89d8-61a42610a89d', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 08:10:43', '-1', 'PAL21081705639');
INSERT INTO `kh_order_info_copy1` VALUES ('53f17fea-f1e2-43e3-b713-138892b1fad3', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:24:13', '-1', 'PAL21081900303');
INSERT INTO `kh_order_info_copy1` VALUES ('53fd7212-283f-4daf-b13f-40fd5ea08993', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 03:50:31', '-1', 'PAL21081702818');
INSERT INTO `kh_order_info_copy1` VALUES ('542e6061-693d-4625-b664-69d92a31a899', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 00:06:27', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5470551d-6ac5-4357-98a0-4cbeba0fdade', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 12:42:52', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('55176a6f-819e-4473-8cce-b1252e7a8c62', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:15:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('557351e2-4517-4223-88ae-c28793d10b8d', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 02:48:54', '-1', 'PAL21081501150');
INSERT INTO `kh_order_info_copy1` VALUES ('559c5f94-30ec-4a79-8181-32ac75cf30dd', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 03:56:41', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('55c9dcb3-89dd-423e-850e-b25ead873965', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:06:33', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('55cce5d2-ee23-4d92-82d0-ed5c28ada712', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 15:48:57', '-1', 'PAL21081816470');
INSERT INTO `kh_order_info_copy1` VALUES ('56499838-0c13-4c03-88c0-d0532b516d2b', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 08:24:06', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('567eb689-fe24-44a1-8836-32924d125dd5', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 14:57:36', '-1', 'PAL21081715037');
INSERT INTO `kh_order_info_copy1` VALUES ('56d4e16e-2a7f-4047-a836-e8326d392966', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 12:03:57', '-1', 'PAL21081812300');
INSERT INTO `kh_order_info_copy1` VALUES ('56f1916a-4b20-4b11-b2a8-b40ee8b62530', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 04:07:08', '-1', 'PAL21081602648');
INSERT INTO `kh_order_info_copy1` VALUES ('56f4e744-d749-4727-acc3-5ef634a37e3b', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 13:34:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('571efc3b-8f34-4455-9c31-eb1cb4a82671', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 03:17:00', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('589fa507-1608-444e-b3e7-85d382a2b678', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 05:30:17', '-1', 'PAL21081503915');
INSERT INTO `kh_order_info_copy1` VALUES ('58b82908-9695-40b9-b160-e59629f34c0b', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:28:52', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('58c0642a-b1f4-4d48-94fe-60bbca974d26', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:01:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('58cd83ba-e43d-44a6-a7b4-8c8675f582d7', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 03:50:29', '-1', 'PAL21081702095');
INSERT INTO `kh_order_info_copy1` VALUES ('58d0b09f-99fd-4067-b3b5-e63a7ec3751e', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:10:51', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5941af32-e0d6-4fe8-bf94-89828ef93947', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:38:25', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('594de596-80bc-4747-adb0-998983f2a712', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 02:49:08', '62', '');
INSERT INTO `kh_order_info_copy1` VALUES ('59738a0e-0803-46f6-8091-81ec5c3f1938', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:23:40', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('59bdac72-ba72-47a5-a9fe-5555dd47495f', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 10:18:38', '-1', 'PAL21081711916');
INSERT INTO `kh_order_info_copy1` VALUES ('59e05b11-94f1-4560-b98c-58bc9475d1d6', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 19:15:52', '-1', 'PAL21081621285');
INSERT INTO `kh_order_info_copy1` VALUES ('59edfe43-33d4-4d1c-bd65-fbc84e6bda8e', 'F9WC-12-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 09:16:21', '-1', 'PAL21081807198');
INSERT INTO `kh_order_info_copy1` VALUES ('5a6a731c-a2b0-4637-90c1-246e3b889943', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 16:08:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5a73d35a-d69b-4065-8fb5-04700f130fcd', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 23:15:50', '-1', 'PAL21081724566');
INSERT INTO `kh_order_info_copy1` VALUES ('5a9c942f-de10-496d-ae55-bda9d12f375b', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 05:21:12', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5aa76ede-e8ec-47e5-97bf-6a39d543f3a3', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 19:44:17', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5ab1f5b8-d24d-4dd0-a412-0d1185af04ed', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 08:59:35', '-1', 'PAL21081507872');
INSERT INTO `kh_order_info_copy1` VALUES ('5ad011f7-5217-41e1-84dc-0ee3ad5e1199', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 12:32:33', '-1', 'PAL21081512097');
INSERT INTO `kh_order_info_copy1` VALUES ('5ba71063-0117-4371-8ebc-1708cdaa0c6c', 'F9WC-13-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 00:10:07', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5bbd7b65-c9b0-48af-9f0b-c7b6bfe01fd8', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 14:46:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5bc45cb0-c595-41f5-af3b-dbb6c95ac78b', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 05:00:03', '-1', 'PAL21081803961');
INSERT INTO `kh_order_info_copy1` VALUES ('5c04fc7a-be6d-4e9d-860d-b838a1d3aeac', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:17:48', '-1', 'PAL21081905702');
INSERT INTO `kh_order_info_copy1` VALUES ('5c0db0f8-2b73-415d-bd24-535c1825dfe8', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:47:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5c1876d7-b8ad-4b44-a731-4192736a019a', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 23:14:15', '-1', 'PAL21081723568');
INSERT INTO `kh_order_info_copy1` VALUES ('5c38ee4b-563f-4bdb-8c36-f324ea7d26cc', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 06:00:54', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5c5891cf-2727-464d-b432-9a75e5ed23f9', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 22:03:00', '-1', 'PAL21081525063');
INSERT INTO `kh_order_info_copy1` VALUES ('5c6adcc2-4bf6-44eb-bcfc-f1161a1a89d6', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:30:46', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5d5724c4-96bc-4d8f-9d2e-3b20eec16ec8', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:09:39', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5d9edc18-601d-4939-b1a5-a5754b0d83e9', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 21:32:10', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5e2795e6-fb4b-4421-a782-a068a12ba87d', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 09:06:16', '-1', 'PAL21081910067');
INSERT INTO `kh_order_info_copy1` VALUES ('5e46adaf-8711-461a-8f26-b9bedb5db33f', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:04:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5e759776-1c3b-4b08-afe1-55084b2c931c', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 05:18:12', '-1', 'PAL21081904109');
INSERT INTO `kh_order_info_copy1` VALUES ('5e982077-fb40-424b-87ba-38faead98dd8', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:23:01', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5ec4ea0a-6489-4b95-ab41-2e21a7c6cb28', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:59:50', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5ef55e8d-ff53-4a61-abec-75c48d57abee', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 06:49:52', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5efc64ab-f960-4909-bbd5-b0720e86380e', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 17:26:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5f0484f0-53c4-4fde-b215-fc2a1ac181dc', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 03:05:07', '62', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5f1c55e7-00e3-415c-b090-4ef754db82c3', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 23:39:48', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5f252969-752d-4058-804f-24582b8b25a1', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 11:33:34', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5f407e39-1941-4437-9572-3133500e6954', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 09:31:40', '-1', 'PAL21081908723');
INSERT INTO `kh_order_info_copy1` VALUES ('5f7bed6f-d377-4363-b963-1857057d1ba8', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 16:06:05', '-1', 'PAL21081916035');
INSERT INTO `kh_order_info_copy1` VALUES ('5f816a9c-11de-4862-85fc-bec2fc4971f3', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:36:28', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5fa6c0a9-9219-487a-b824-4c6f8faa7c5f', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 06:00:44', '-1', 'PAL21081904673');
INSERT INTO `kh_order_info_copy1` VALUES ('5fb3a9ac-21da-43cf-86fc-6737c05bbb21', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:54:04', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('5fe00769-a64f-4e78-a084-12696b84c21d', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:17:55', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('608d2924-509e-4faa-980b-f19451c24ad9', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 18:19:29', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('60d3ea85-af04-43d4-9a92-7801f1f4e9c9', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:52:20', '-1', 'PAL21081906501');
INSERT INTO `kh_order_info_copy1` VALUES ('60d43fa9-5ca8-4e1d-a7d1-226ee406c02e', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 17:28:31', '-1', 'PAL21081517947');
INSERT INTO `kh_order_info_copy1` VALUES ('60f68c93-4765-4e10-806e-9b2cd1101616', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:14:05', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6199ef21-6f02-493a-aa13-a799cad00206', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 05:56:38', '-1', 'PAL21081806828');
INSERT INTO `kh_order_info_copy1` VALUES ('61d125bc-b9f7-4b40-bd08-016bfe5c1214', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:30:31', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6242ebe4-421e-449b-98a7-1c2685376869', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 15:59:47', '-1', 'PAL21081616321');
INSERT INTO `kh_order_info_copy1` VALUES ('62d2a31a-dd53-49d7-afbc-82b9a280e634', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:53:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('63193edd-1381-45d0-a27d-a2fabe962e83', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:06:07', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6321d0ab-75ad-4a22-9d98-cb18422d8162', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 23:02:01', '-1', 'PAL21081625653');
INSERT INTO `kh_order_info_copy1` VALUES ('6368cff0-39c3-43f8-8543-5181b61c0f9e', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 10:14:03', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('63ee3a00-8741-4c98-8f5c-c17601e86a1b', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:19:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('643be4f9-c765-4f4b-92e1-b9998c274d32', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 23:02:03', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('644a3801-e5cd-43a7-842d-ad167aa176ee', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 05:01:20', '-1', 'PAL21081903470');
INSERT INTO `kh_order_info_copy1` VALUES ('6473918c-2aea-469a-b314-f5d7d68a79e8', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 06:33:12', '-1', 'PAL21081503579');
INSERT INTO `kh_order_info_copy1` VALUES ('64b0977c-17fd-403c-822d-9ed11feb9dd9', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 23:24:20', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6503a5f3-e002-4923-b713-003f6bc99cea', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:24:07', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('65549415-1102-4051-94b8-17b4b3b13e0e', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 05:00:02', '-1', 'PAL21081903749');
INSERT INTO `kh_order_info_copy1` VALUES ('65e4c9a5-93f6-46fa-91ac-095e9fbc156c', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 23:11:50', '-1', 'PAL21081623992');
INSERT INTO `kh_order_info_copy1` VALUES ('65fdbee6-baca-4258-b077-35cfe544a02d', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 07:04:19', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6620a653-f8c4-4e86-ad76-c608c6529223', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 14:21:28', '-1', 'PAL21081614030');
INSERT INTO `kh_order_info_copy1` VALUES ('663f62de-4e6d-48d8-b878-c066deb4438f', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 10:58:58', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('667a4b3d-3be8-4872-a027-8e28854cfce9', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 10:58:56', '-1', 'PAL21081810873');
INSERT INTO `kh_order_info_copy1` VALUES ('68542a09-45b0-45a2-80a6-5893b5811a42', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 14:23:54', '-1', 'PAL21081516036');
INSERT INTO `kh_order_info_copy1` VALUES ('68951195-15a9-4dd8-9b37-985c2b56380d', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 15:18:10', '-1', 'PAL21081815126');
INSERT INTO `kh_order_info_copy1` VALUES ('68d28c05-2fa5-4af1-9448-1b5f9e6ce982', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 09:20:15', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('68e76c8e-fd07-4446-b8cf-ac5d12941029', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 15:38:21', '-1', 'PAL21081716353');
INSERT INTO `kh_order_info_copy1` VALUES ('694c3483-e72e-4758-a88b-1b1a228c533c', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 19:17:03', '-1', 'PAL21081419691');
INSERT INTO `kh_order_info_copy1` VALUES ('694f731a-577d-42d9-9dd4-3472f105dcde', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 18:10:52', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('698d22b1-5d18-4a1d-8e88-32ee973678c5', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:34:22', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('699efac1-749e-4fab-a747-c53cc2507852', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:01', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('69b7709d-3672-493b-915a-8dd71b9890a9', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:29:35', '-1', 'PAL21081901160');
INSERT INTO `kh_order_info_copy1` VALUES ('6a3e8fb5-5265-488f-b2cb-18d2b83e10f9', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 01:34:16', '-1', 'PAL21081700167');
INSERT INTO `kh_order_info_copy1` VALUES ('6a71cd42-d672-4970-be90-2950f0cd074c', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6ab51688-5232-4ead-939c-43bcbe0970f2', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 11:07:12', '-1', 'PAL21081510449');
INSERT INTO `kh_order_info_copy1` VALUES ('6ab902e1-19e0-4cec-b76f-c100f65026af', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 09:56:56', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6ae38128-226e-421d-a601-cb14c02a8e09', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 01:10:04', '-1', 'PAL21081424489');
INSERT INTO `kh_order_info_copy1` VALUES ('6ae78037-11d3-49f1-9024-2a4803d32624', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:06:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6b2d7dda-94c2-436b-bef6-cc906bd58dae', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 20:26:57', '-1', 'PAL21081721394');
INSERT INTO `kh_order_info_copy1` VALUES ('6be1c2ae-344b-4e8e-8b86-29366b89988d', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 10:15:01', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6c104b43-62d9-4901-b2ba-26e9f15f6f5d', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 16:56:57', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6c3f10ae-1e42-43c3-bf57-25c31f8c8e8f', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:15:18', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6c622d0b-be74-4b9f-88e3-74a1a4189822', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:33:17', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6c7ff342-6c39-4fae-9651-c2acdc375124', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 02:56:02', '-1', 'PAL21081801637');
INSERT INTO `kh_order_info_copy1` VALUES ('6ca16e91-2a4e-49a2-b1b2-0cf6d18c82e1', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 23:39:17', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6cdaaee5-319d-4b37-a0de-f94f2bc5b338', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 13:18:38', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6d254f4d-dbbe-487f-9ed3-0ad3ff69c11c', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:22:27', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6d68f25d-f0d2-4652-86ea-0d7efe51221d', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 04:53:59', '-1', 'PAL21081503599');
INSERT INTO `kh_order_info_copy1` VALUES ('6d6b6489-ce15-495d-ae23-17b93d647598', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 07:39:23', '-1', 'PAL21081604805');
INSERT INTO `kh_order_info_copy1` VALUES ('6e10e27a-e312-4b8a-b243-e96a81e0d0f7', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:11:25', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6e5975a6-3462-440c-a08e-4ac7a9acbf3c', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 10:17:42', '-1', 'PAL21081909547');
INSERT INTO `kh_order_info_copy1` VALUES ('6e7cbced-928b-47b6-9907-793137fda831', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 05:40:58', '-1', 'PAL21081804367');
INSERT INTO `kh_order_info_copy1` VALUES ('6e917702-18be-47f5-a1d6-b0f41fd22b33', 'F9WC-12-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 22:51:20', '-1', 'PAL21081819972');
INSERT INTO `kh_order_info_copy1` VALUES ('6ebc4ea9-486d-43e4-b55a-aa6c5e9eeebf', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 09:08:20', '-1', 'PAL21081708706');
INSERT INTO `kh_order_info_copy1` VALUES ('6f1e728c-7afa-4919-a3cd-4513872ef2ff', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 03:35:29', '-1', 'PAL21081501736');
INSERT INTO `kh_order_info_copy1` VALUES ('6f2e2b0f-6c8a-489c-afa7-0698adf34312', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 03:59:56', '-1', 'PAL21081702477');
INSERT INTO `kh_order_info_copy1` VALUES ('6f41fa48-a0e7-4385-9bc0-927e3e1ce4b8', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 21:21:12', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6f87c96a-28e4-4d22-9e48-7720d0ee48a2', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:29:49', '-1', 'PAL21081900901');
INSERT INTO `kh_order_info_copy1` VALUES ('6fba9883-3e21-43c8-889d-924f9244f2ff', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:10:07', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6fc361ee-8827-486d-b9eb-2d379a45cc2b', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:02:29', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6fd0dcbb-2020-442a-8f7a-1a42c5f30f82', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 04:47:29', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6fdc110f-113d-414c-a8a2-723e3db2146b', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:15:18', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('6fed2a79-a385-451c-924b-cf16a7393371', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 09:47:40', '-1', 'PAL21081811286');
INSERT INTO `kh_order_info_copy1` VALUES ('70dbfc46-c3b3-4eae-b01c-b14761aff4f1', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 10:06:13', '-1', 'PAL21081709424');
INSERT INTO `kh_order_info_copy1` VALUES ('71196004-4ca0-4e93-8550-b9078494e871', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 18:58:38', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('71c38c8e-b2c5-4686-9b1e-50562e0c60da', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 03:50:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('71c6a0ac-181b-4b73-8f37-c4ada4ab8b71', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 14:31:52', '-1', 'PAL21081815226');
INSERT INTO `kh_order_info_copy1` VALUES ('720320e5-7390-405f-8acd-4068072cc78f', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 04:00:24', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7219a846-1d7d-4592-a21a-9b348880c0b4', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 21:26:11', '-1', 'PAL21081823057');
INSERT INTO `kh_order_info_copy1` VALUES ('72739d4c-955a-4acc-8329-be1462b7e774', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 23:01:41', '-1', 'PAL21081524133');
INSERT INTO `kh_order_info_copy1` VALUES ('72fa9a60-058c-44ee-b38b-9d63930cc1fd', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:34:30', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('730bb871-ed05-4908-bedf-5fd5722a388e', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 11:16:30', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7347dbef-f99b-4b2f-95f9-4242dc379ee0', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 22:21:26', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('74195156-dccc-4b0b-9dae-6d5bec6e0d96', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 04:54:17', '-1', 'PAL21081704206');
INSERT INTO `kh_order_info_copy1` VALUES ('741efd21-df17-4a71-b1cb-dcdb4378c846', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 00:52:43', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('742d1988-8a0c-4b99-9b36-f1b4c30fd07c', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 17:38:58', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7432ddf7-30f0-4142-a8be-ea01680253dc', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:17:54', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('74434f4c-3b73-4797-a40b-0616d66ff1c0', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 19:17:39', '-1', 'PAL21081519510');
INSERT INTO `kh_order_info_copy1` VALUES ('746e33ec-a077-4eb0-a0c4-1ab02c92fffc', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 11:53:21', '-1', 'PAL21081509217');
INSERT INTO `kh_order_info_copy1` VALUES ('74fe14ce-9d05-4e74-aa44-427795253808', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 16:23:07', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7518c6f1-de71-4d7d-ab66-087a8e462e5f', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 22:29:49', '-1', 'PAL21081523687');
INSERT INTO `kh_order_info_copy1` VALUES ('75a63488-2c16-4154-8707-74a24791cb45', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 17:19:09', '-1', 'PAL21081617255');
INSERT INTO `kh_order_info_copy1` VALUES ('7628f319-d71b-4ebf-89dc-468afe36c243', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 01:43:00', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7631a48e-5463-416a-a44c-a2c6b96bfd27', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 14:46:16', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('76703b3a-f869-46c3-b563-18cefa945cfa', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:14:48', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('76766658-79aa-4ee4-acc0-97dd000b6449', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 20:34:27', '-1', 'PAL21081721875');
INSERT INTO `kh_order_info_copy1` VALUES ('7676c3cc-4304-4b57-adb0-f9de77307ee8', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:06:33', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('76f7dff6-0776-4028-894c-5f9210ddd077', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 19:04:29', '-1', 'PAL21081820350');
INSERT INTO `kh_order_info_copy1` VALUES ('77109835-5682-41e7-a8a7-51aa6c9c9a85', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-15 02:18:03', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('772baf4a-a383-4282-b93e-960db851ad0c', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 20:07:52', '-1', 'PAL21081417842');
INSERT INTO `kh_order_info_copy1` VALUES ('774d79f4-76f1-40a3-aaff-811a128e2c0f', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 11:02:54', '-1', 'PAL21081511051');
INSERT INTO `kh_order_info_copy1` VALUES ('776a8f0f-df46-4731-93e1-20538cb6fab4', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 10:59:56', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('780de6a8-110f-4c41-90b2-25b71d7de348', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:26:39', '-1', 'PAL21081901715');
INSERT INTO `kh_order_info_copy1` VALUES ('781e7937-fd1f-41c6-804e-cd994f82bee6', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 06:43:10', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('787ce8ad-4b12-4371-9628-cced4cca3f3b', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 06:36:59', '-1', 'PAL21081605049');
INSERT INTO `kh_order_info_copy1` VALUES ('789ea804-ad8d-4e54-a87e-0bf511127173', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 04:21:34', '-1', 'PAL21081702767');
INSERT INTO `kh_order_info_copy1` VALUES ('796c37c7-d4b7-4cc4-a5eb-a7a956fa6bda', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 01:24:50', '-1', 'PAL21081727887');
INSERT INTO `kh_order_info_copy1` VALUES ('79b7eeb7-0a86-4550-8bd6-185f38014fc6', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 12:33:01', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('79f3c51a-eca5-491a-9bba-8b77bc6fdfdc', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:30:50', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7a38191f-4198-464f-9890-38ecb06824fb', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 07:09:11', '-1', 'PAL21081606775');
INSERT INTO `kh_order_info_copy1` VALUES ('7a43fdc8-aec3-47df-8b0b-6476fd280c08', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 18:09:48', '-1', 'PAL21081520431');
INSERT INTO `kh_order_info_copy1` VALUES ('7ac69674-3b68-426d-aae6-6bae2676f092', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 00:29:28', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7aca5141-a1b8-4ce6-b3c1-8837761aa087', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 21:17:28', '-1', 'PAL21081623581');
INSERT INTO `kh_order_info_copy1` VALUES ('7b63ef1c-6a22-43e7-b96e-f2d7cffb2782', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 05:21:07', '-1', 'PAL21081905665');
INSERT INTO `kh_order_info_copy1` VALUES ('7b91b567-fe95-4570-8a5c-1c1b43ff3e2a', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 13:41:15', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7bf1ac0e-a35d-418d-b530-074d4770001a', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:39:23', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7c013df2-7dd9-4946-a75e-d60c1a883865', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 05:00:05', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7c7a7205-e652-41af-85bb-8b492b96ed3a', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 05:07:04', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7caa028a-c165-4c33-9d73-ed441e7c44c6', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 09:06:32', '-1', 'PAL21081507830');
INSERT INTO `kh_order_info_copy1` VALUES ('7cbcbc5f-e338-433c-b432-f3dc92728036', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 12:53:45', '-1', 'PAL21081513050');
INSERT INTO `kh_order_info_copy1` VALUES ('7d15426a-b290-4a74-b681-1ff9b0540409', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 20:58:47', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7d3a2fb0-4044-4a49-bfa8-8ff5dbf35155', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 23:51:34', '-1', 'PAL21081524423');
INSERT INTO `kh_order_info_copy1` VALUES ('7d8a5379-7ffa-4268-bc6b-aafcdd4c83e2', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 12:30:58', '-1', 'PAL21081910667');
INSERT INTO `kh_order_info_copy1` VALUES ('7d8c93c7-8742-4d66-9d09-843eb31ce2a8', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 10:55:37', '-1', 'PAL21081910608');
INSERT INTO `kh_order_info_copy1` VALUES ('7dabcd81-7136-46a7-b858-7924d9bf92e6', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 16:56:54', '-1', 'PAL21081817802');
INSERT INTO `kh_order_info_copy1` VALUES ('7e2560b0-113e-4cb2-a9ac-d0172cbb8f4a', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:12:24', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7e694c7f-79a0-406e-8d6b-9e9b61a89b88', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 05:43:08', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7ec16f2e-b476-4dcd-bc32-9586a7e829f8', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:28:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7ef5669a-a646-49b4-86ff-b2c88c28f42a', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 13:41:09', '-1', 'PAL21081714324');
INSERT INTO `kh_order_info_copy1` VALUES ('7f238732-c8ce-4a89-93d0-a5cdd0f3d16f', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:16:35', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7f829046-01c9-43b2-8dc5-89ea02d37718', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 14:58:44', '-1', 'PAL21081514678');
INSERT INTO `kh_order_info_copy1` VALUES ('7f836e14-ae10-43b2-8c01-572f05a0294e', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 04:30:02', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('7f910b73-53b2-42e4-a134-5e6a60f6be07', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 05:16:07', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('80acd222-bacd-42a6-bae9-c1e3b7a06433', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:27:29', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('80c734a7-0e88-46c7-ac9a-f91a7b422118', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 06:44:06', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('810be569-e78d-413d-b95e-75717bd44d76', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 10:59:39', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('81122afe-f487-452f-b93c-c9d63bfcb38b', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:17:55', '-1', 'PAL21081425048');
INSERT INTO `kh_order_info_copy1` VALUES ('81386c35-47f4-4285-97b2-4dd467f3e086', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 19:19:37', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('814a8e9c-2638-4601-9430-ed9657417714', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 07:40:43', '-1', 'PAL21081608669');
INSERT INTO `kh_order_info_copy1` VALUES ('8154ea29-7cdb-4884-9842-8609411310f9', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:33:59', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('81c6e057-0081-4dc3-a2cc-612e5f6db831', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 05:22:52', '-1', 'PAL21081502808');
INSERT INTO `kh_order_info_copy1` VALUES ('81c724bd-b615-45c0-841b-d0198a3a5e48', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 20:39:27', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('82b67061-84d6-4695-a6ae-c58b6814ac65', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:11:02', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8381dcde-604a-4e1d-b39a-f532649b0bdb', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 23:57:11', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('838f049a-0ad0-4776-91d0-ce5f17cbd3f2', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 13:34:30', '-1', 'PAL21081513313');
INSERT INTO `kh_order_info_copy1` VALUES ('840b755b-5502-466c-91f5-6934f27175c6', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 16:20:27', '-1', 'PAL21081518331');
INSERT INTO `kh_order_info_copy1` VALUES ('842275f2-7b12-4ec5-abad-f987134a69d7', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:19:06', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8434eb2b-8334-4d2b-bd83-21dff0055512', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:42:59', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('84c46e9d-970b-4e80-b157-80392f27e445', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 22:49:19', '-1', 'PAL21081623296');
INSERT INTO `kh_order_info_copy1` VALUES ('857fc7a3-6183-448f-ab49-0f1adb7d8862', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:06:12', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('85ccfd4a-0f6c-482f-b13e-062c650c70a0', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:59:58', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('85d34250-4ab7-4e3d-8603-afc8f3fbab32', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 18:06:13', '-1', 'PAL21081617971');
INSERT INTO `kh_order_info_copy1` VALUES ('85fb8dfe-8964-4505-9a46-d85320536a92', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 11:50:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('862a3f95-9417-4660-a6c4-c833cb9384c7', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 13:26:02', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8682877e-fbb8-41f6-a78c-0d5289c8f606', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 14:10:21', '-1', 'PAL21081716245');
INSERT INTO `kh_order_info_copy1` VALUES ('86e870b6-1200-4b43-8539-72688d8247dd', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 04:47:25', '-1', 'PAL21081705523');
INSERT INTO `kh_order_info_copy1` VALUES ('87345fe1-b173-4ac1-9081-4de6f552acb0', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:27:24', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('87b8956c-db89-4496-b7a5-9ce804ec13c5', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 16:22:31', '-1', 'PAL21081915018');
INSERT INTO `kh_order_info_copy1` VALUES ('87bad4de-bea5-457c-bc23-f2bfa27a5a0b', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:09:01', '-1', 'PAL21081900359');
INSERT INTO `kh_order_info_copy1` VALUES ('87de64f9-c077-4b5b-8644-a9929b60d5bf', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:42:01', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('88058a5b-233a-49a8-8bce-65e4ee50aa3c', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 16:15:43', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('882d7acd-7715-4a5e-a9d9-5b9868421ff9', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 23:11:49', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('882e7e94-54b2-47d6-8db3-5462029c7be9', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 12:57:26', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('883cea74-a059-447f-a711-602ae50f9d32', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 22:01:31', '-1', 'PAL21081620955');
INSERT INTO `kh_order_info_copy1` VALUES ('883e5015-a2ae-4f50-84ac-fcbab30269f0', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 14:51:45', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8855cb9d-d858-4ddf-a120-e71391914608', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 12:32:58', '-1', 'PAL21081512046');
INSERT INTO `kh_order_info_copy1` VALUES ('8862ba21-6de4-4de3-93b8-74ba12bc73ce', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 15:01:57', '-1', 'PAL21081910894');
INSERT INTO `kh_order_info_copy1` VALUES ('88c5df50-4665-4315-b8ea-30a8b9c5793a', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 07:10:02', '-1', 'PAL21081806621');
INSERT INTO `kh_order_info_copy1` VALUES ('88d27500-1073-49f3-8a84-e7b3f771a3c3', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:56:21', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('89051140-ca08-480b-b09b-00ebae2cb5e7', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 10:17:39', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('89066ef1-a494-4468-84bc-5e64bda89cdc', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 05:48:39', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8928e4ad-6e90-4a92-8a3d-fc7ec11fa967', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 18:35:43', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('89e04e79-3044-4831-ad4f-5a82688e6f04', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:54:49', '-1', 'PAL21081516000');
INSERT INTO `kh_order_info_copy1` VALUES ('8a3127d2-8758-4379-929a-ede36648446c', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 01:24:56', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8a520e8e-5644-44ae-933b-fdd7a9085263', 'F9WC-12-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-14 23:14:32', '-1', 'PAL21081417028');
INSERT INTO `kh_order_info_copy1` VALUES ('8a56aaaa-5891-4762-aaa6-569784734cb8', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 23:56:09', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8a63047f-4e76-497e-a811-72b699ae9f5e', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 18:48:58', '-1', 'PAL21081819652');
INSERT INTO `kh_order_info_copy1` VALUES ('8a83c6be-1593-44c2-a9ce-9e66cc9e0d47', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-15 01:33:37', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8ad1c49f-0e08-464a-a58d-062b491e4e96', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 10:30:35', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8b1429ff-2a0c-4e58-9955-fee50b7ef073', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:10:46', '-1', 'PAL21081514879');
INSERT INTO `kh_order_info_copy1` VALUES ('8b45cc6a-6e8e-4561-89c4-951e24605799', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 04:56:47', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8b46fe0c-6602-425c-9473-d0148eb83430', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:28:01', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8b48559d-252f-4be5-8fdb-e7af15f32d86', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 07:59:20', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8b69e6a4-ee03-40f7-b906-272d6369e3ef', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 09:51:50', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8b79a09f-6ff5-4189-a636-87a863d6aa43', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 04:53:27', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8bcec622-9b4d-44e5-96a8-da29ab57f8b1', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 15:20:22', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8bf1f5be-3fa8-4525-ab29-0708a16c3db8', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:47:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8c0860cf-9849-44ca-a155-9870fd712a64', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 23:14:32', '-1', 'PAL21081416943');
INSERT INTO `kh_order_info_copy1` VALUES ('8c85928f-2878-44f0-a96f-fd2fa930a76f', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 17:12:01', '-1', 'PAL21081916538');
INSERT INTO `kh_order_info_copy1` VALUES ('8c9c5e53-4dc3-4cbe-b74a-30a34e5a5bd4', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:05:14', '-1', 'PAL21081514434');
INSERT INTO `kh_order_info_copy1` VALUES ('8cb444f8-5511-468b-8f14-2c0d23ca390b', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 02:00:28', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8ce39b97-89ab-41cd-8343-3ff8aed2dda8', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:10:08', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8ce70338-476c-4ae3-9339-3d1039a1e344', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 11:51:53', '-1', 'PAL21081711507');
INSERT INTO `kh_order_info_copy1` VALUES ('8d3186a1-615b-43fa-8678-32688d84685f', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 05:20:57', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8d63411a-ff57-44a4-9a49-cda376553647', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 10:28:41', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8dc5d3ab-178e-45d3-82c0-952518af70d8', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 13:43:27', '-1', 'PAL21081815894');
INSERT INTO `kh_order_info_copy1` VALUES ('8dc99ac4-5931-41e8-920d-db615286dc8b', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 05:21:24', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8de7a725-99aa-4704-b489-1635f8a4513e', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 09:47:45', '-1', 'PAL21081509006');
INSERT INTO `kh_order_info_copy1` VALUES ('8e13e8b1-5118-4ba1-a759-53488f6f9347', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 09:43:44', '-1', 'PAL21081508829');
INSERT INTO `kh_order_info_copy1` VALUES ('8eb06993-4853-44c9-b80a-d893bfb7804c', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 11:31:49', '-1', 'PAL21081811487');
INSERT INTO `kh_order_info_copy1` VALUES ('8eef7321-3d24-4b5c-8045-e12be70dd507', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 12:10:39', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8f89bd78-3102-4267-ac97-e9ff3f332e8c', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:59:56', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('8fa97242-8a30-44c5-bcd0-93a0d0f769e6', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:59:43', '-1', 'PAL21081516030');
INSERT INTO `kh_order_info_copy1` VALUES ('9066cce9-7107-4912-88ed-dddf6b958c3e', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 11:09:32', '-1', 'PAL21081910367');
INSERT INTO `kh_order_info_copy1` VALUES ('911fa58d-6d3e-472c-9b3d-844f99c2c861', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:33:55', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('91a0cc99-c9f3-4d18-86e0-7fe0560efb7c', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-14 21:15:14', '-1', 'PAL21081422067');
INSERT INTO `kh_order_info_copy1` VALUES ('91a22a4b-407d-4595-814d-679e3a19c435', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:18:16', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('91df3d1c-27aa-433c-8462-4817786194ab', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 14:33:38', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9214534f-5027-41a5-871c-6050681d4d26', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 04:29:59', '-1', 'PAL21081903436');
INSERT INTO `kh_order_info_copy1` VALUES ('921542e4-809b-4681-87b3-26d945c8d669', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 13:53:47', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('922f1ff4-4c3f-4a2c-a189-a547927697c7', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 09:03:49', '-1', 'PAL21081908475');
INSERT INTO `kh_order_info_copy1` VALUES ('923adfbb-810c-422b-8770-1b1f046c9f27', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 16:00:32', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('926eb3a4-505d-4f3b-bbd2-5e12e6fcd430', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 13:05:40', '-1', 'PAL21081812941');
INSERT INTO `kh_order_info_copy1` VALUES ('92789316-8038-4d35-8f4d-9cdaa47551b9', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 15:50:42', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('929ee3ff-705f-4152-af94-bf3e0a1b4dce', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 11:49:54', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('92c83cf5-874e-45c5-8281-a43f37ec56cf', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 23:51:07', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('92f25ba3-1c3d-45a3-94cd-addf8f589e5c', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 08:59:41', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('93580e22-c3a3-4b8a-abaa-3950d26ecf75', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 14:21:40', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('935e1120-bf0a-457f-8cd1-5db88c5cfb83', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:31:39', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('93e123a8-7cca-4cac-8adb-54e9fe2c3a19', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 22:06:33', '-1', 'PAL21081824984');
INSERT INTO `kh_order_info_copy1` VALUES ('93e37421-2946-4e29-89a9-7e4efb8064f6', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 22:56:35', '-1', 'PAL21081524319');
INSERT INTO `kh_order_info_copy1` VALUES ('940fed75-9345-4c79-8bd2-fc4113be362e', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 10:34:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('941ae73f-07a7-40db-bdc3-00c2bd2b3089', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 22:32:52', '-1', 'PAL21081723867');
INSERT INTO `kh_order_info_copy1` VALUES ('942874b1-ef2e-4131-8330-c11789f16e30', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:13:34', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('942f5f66-c7fd-4def-b029-dadfecc333a7', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 11:38:18', '-1', 'PAL21081610860');
INSERT INTO `kh_order_info_copy1` VALUES ('945eab90-8b2e-4246-9c8a-22207fa50034', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 09:30:13', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('946541de-cc5e-4f2b-a481-d5eec7a48ba6', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:57:47', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9473d944-e2a9-47a2-90f4-1eaf6d9e2576', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 07:11:41', '-1', 'PAL21081906201');
INSERT INTO `kh_order_info_copy1` VALUES ('948c2ae8-4bb1-4771-a355-3ad1391763ef', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 02:01:24', '-1', 'PAL21081527176');
INSERT INTO `kh_order_info_copy1` VALUES ('9495036c-944e-4bfe-98b3-a5c20aac8061', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 18:57:03', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('94a1a72e-2beb-4b73-b5ef-3e7552c11bc6', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 07:43:39', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('952b3406-c866-41fe-ab48-b22aa0a8a60e', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 05:41:01', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('952d2df8-3ddd-4810-a157-caf0bf09f897', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 10:38:09', '-1', 'PAL21081508098');
INSERT INTO `kh_order_info_copy1` VALUES ('9537d25a-ac3e-417f-b970-1218987b1848', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:19:43', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('958a1e86-b7eb-4946-abb3-48ad9d2742e0', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:20:03', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9593e947-d8a7-46f9-a285-330451d229bc', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:25:43', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('95b4f935-4a07-4627-bc80-764540fe4b39', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 05:48:27', '-1', 'PAL21081704684');
INSERT INTO `kh_order_info_copy1` VALUES ('95dfd79b-d916-4f46-8391-76bd31e0731a', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 12:31:34', '-1', 'PAL21081612689');
INSERT INTO `kh_order_info_copy1` VALUES ('961cb3f9-8d31-456c-bdd1-96d4d0c58c60', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:04:44', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('961eea5e-5c1f-42e7-abd5-6703b4137dba', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 07:55:43', '-1', 'PAL21081809205');
INSERT INTO `kh_order_info_copy1` VALUES ('9627bd4f-018e-4c02-806d-bf295585061d', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:59:43', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('965f3f53-f61a-4fd2-a42e-be3f3ee1921d', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 15:03:59', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('96cef643-b7a4-492a-a2af-f553a7ebb082', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:31:52', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('97ae0ac0-3de6-4b5a-9749-7c98e6380515', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:45:44', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('97e48d4c-0f8d-47e9-a235-f7381127dbc3', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 18:10:49', '-1', 'PAL21081819433');
INSERT INTO `kh_order_info_copy1` VALUES ('9807f942-4d42-45e2-8989-ae4e7892d559', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 16:40:00', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9818c1a8-d522-4b60-b101-ccb0cd6cfaa1', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 22:06:33', '-1', 'PAL21081823702');
INSERT INTO `kh_order_info_copy1` VALUES ('983e42d7-9ed2-48f7-8346-cd63c05865d6', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 11:53:20', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('98773746-d322-4491-883a-17906650f995', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 09:15:57', '-1', 'PAL21081708586');
INSERT INTO `kh_order_info_copy1` VALUES ('98ca2015-6922-4a33-901b-a1e247e99f04', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:32:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('98d36511-8e0e-425a-b924-51fa95572810', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 08:09:22', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('98e4b44a-09b3-492f-81e6-e98709cde293', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 08:38:21', '-1', 'PAL21081509466');
INSERT INTO `kh_order_info_copy1` VALUES ('9927d833-e4f2-41cb-96cb-4da248711b7b', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 20:07:53', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9a8a7864-86ab-49ca-8441-3ec88c0fc5c7', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 06:04:33', '-1', 'PAL21081905275');
INSERT INTO `kh_order_info_copy1` VALUES ('9a903106-8cba-4d3c-b584-e0d1997e6cf0', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 09:48:31', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9a94455f-d3fe-4a84-ad87-39eb4aa3073d', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 17:44:35', '-1', 'PAL21081716163');
INSERT INTO `kh_order_info_copy1` VALUES ('9ab75263-874f-49c0-aef5-d2ce0891366c', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 07:18:01', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9ab7ce53-2fa0-4746-9dfc-9701acf58b88', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 20:14:59', '-1', 'PAL21081821250');
INSERT INTO `kh_order_info_copy1` VALUES ('9ab9567f-2078-4f50-a712-ee387c7b9513', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 19:43:42', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9b00273e-1105-4223-97ab-945cb1012f76', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 01:10:32', '-1', 'PAL21081526593');
INSERT INTO `kh_order_info_copy1` VALUES ('9b2b39f0-a164-4701-bd16-624e104264a1', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 21:21:10', '-1', 'PAL21081622053');
INSERT INTO `kh_order_info_copy1` VALUES ('9b69a563-b298-496d-be50-849992bdf174', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 09:57:11', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9c08decb-f6a5-4a47-b08b-0e603882a467', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9c3914c5-6fd1-4a54-b64d-1f1bb893c4ab', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:13:50', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9c663413-c283-407a-87bb-0e3fa59fd927', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 08:43:00', '-1', 'PAL21081604246');
INSERT INTO `kh_order_info_copy1` VALUES ('9c8af815-1f17-4460-992a-30f25d626e6a', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 06:30:42', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9ca224c5-01ee-45fe-bc8e-958a3edbce6d', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 11:09:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9cc5ae35-84d9-4558-b16e-cfb46121cc26', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 23:24:18', '-1', 'PAL21081624456');
INSERT INTO `kh_order_info_copy1` VALUES ('9cda54b3-de5b-4dfd-8705-c1383ca08a39', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:16:01', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9cdc82aa-e38c-4563-8a1c-6e9272e2ab08', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 10:14:01', '-1', 'PAL21081909379');
INSERT INTO `kh_order_info_copy1` VALUES ('9d2110d0-a173-4e8e-a8e6-606f6b33801f', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 06:39:36', '-1', 'PAL21081707658');
INSERT INTO `kh_order_info_copy1` VALUES ('9d21bbe6-49b1-49ab-a262-f230e75a9b00', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 03:31:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9d23a88d-2646-4f1b-b85c-efdd31b5ce47', 'F9WC-13-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 03:30:06', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9d28ee66-9473-4bc1-969e-e899bbe101c5', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 06:11:14', '-1', 'PAL21081604813');
INSERT INTO `kh_order_info_copy1` VALUES ('9d60b160-b672-429d-8394-7eecccda9dc0', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 09:56:44', '-1', 'PAL21081509084');
INSERT INTO `kh_order_info_copy1` VALUES ('9e193a69-d3aa-4d4f-97bd-0e6e09ffaf65', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 13:26:01', '-1', 'PAL21081513354');
INSERT INTO `kh_order_info_copy1` VALUES ('9e572822-c49f-4e6f-857f-5120aa93f0b2', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 22:47:41', '-1', 'PAL21081623192');
INSERT INTO `kh_order_info_copy1` VALUES ('9e8cc55d-aadc-4ac5-9242-d48a4ab54f32', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 17:25:58', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9f0d65ee-33b3-4572-b6bb-4dac6dde666c', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 21:21:37', '-1', 'PAL21081824633');
INSERT INTO `kh_order_info_copy1` VALUES ('9f180ef9-b2a9-4543-afe4-7a30933cef80', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 16:05:32', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('9f190f03-e267-469c-a560-fe2df568a765', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 01:33:26', '-1', 'PAL21081700128');
INSERT INTO `kh_order_info_copy1` VALUES ('a037bc3c-d000-4947-a202-4237817d48c6', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 04:31:50', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a09bda35-12dc-4c82-b145-e47b27fe414e', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 12:28:23', '-1', 'PAL21081513882');
INSERT INTO `kh_order_info_copy1` VALUES ('a0d26e52-0874-4bf7-a5e1-8b8fb5929623', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 17:25:45', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a11ee2a8-628d-43a4-9c45-a45fea06efb0', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 17:57:07', '-1', 'PAL21081518223');
INSERT INTO `kh_order_info_copy1` VALUES ('a14f506c-42ed-49e8-871c-d3e9ac76874e', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:49:29', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a152d6c0-6c36-4156-aade-14c30150339e', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:48:55', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a175e697-3746-49fd-93c4-2d28dd0f454b', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 21:11:22', '-1', 'PAL21081822111');
INSERT INTO `kh_order_info_copy1` VALUES ('a177069e-ae96-4999-b743-5c133f09543b', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:49:31', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a1e9dd2a-a228-4884-a69d-639d80d7e4ab', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 18:13:10', '-1', 'PAL21081518778');
INSERT INTO `kh_order_info_copy1` VALUES ('a21be5ff-ef05-4234-978d-b7f3a580a387', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 10:49:47', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a227130c-8c8d-422b-a5af-ffddfbac07a7', 'F9WC-11-1', '', '2', 'OVER', 'GOODS', 'CARRY', '2021-08-19 17:53:21', '-1', 'PAL21081918104');
INSERT INTO `kh_order_info_copy1` VALUES ('a25e2a5b-9c66-4553-bc3a-85a13d88fe4f', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 06:46:13', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a2ad494c-8160-4927-a6d1-eedd0d76c67c', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 18:05:58', '-1', 'PAL21081518196');
INSERT INTO `kh_order_info_copy1` VALUES ('a2deb7d7-e2e9-42a3-8740-dce201738290', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 07:27:17', '-1', 'PAL21081806822');
INSERT INTO `kh_order_info_copy1` VALUES ('a3b70376-a258-4c39-85d8-596f20539ec8', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 11:35:33', '-1', 'PAL21081710609');
INSERT INTO `kh_order_info_copy1` VALUES ('a40ee1e7-5350-4c08-a86e-3096023b0f18', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:06:09', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a439717b-bcfe-417c-a0df-b151999775c2', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:25:18', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a44e9a64-06ff-4409-a77b-911fd15c3ad2', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:01:04', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a4828b7c-c287-4794-a857-8ec048691ea2', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 07:42:30', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a5014527-9cdc-4ef5-9d05-e03722d7d032', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 23:56:06', '-1', 'PAL21081525618');
INSERT INTO `kh_order_info_copy1` VALUES ('a50a8d99-bb0b-4a14-a44c-154956e45a23', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 08:58:30', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a51a6fef-730a-4d3d-8fac-1210ac1e8f9e', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:42:59', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a55db5c9-40d3-418e-9973-2241e0eee373', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:55:50', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a56bb071-273b-4b80-abcf-44b071ffdfa3', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:50:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a575d3a1-a04e-448b-a529-8790541bce41', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 03:42:11', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a5cfeb44-933d-489b-94de-fb1bba977f32', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 00:56:18', '-1', 'PAL21081524888');
INSERT INTO `kh_order_info_copy1` VALUES ('a5e848db-7bde-43ca-b5ef-3e9871dd8157', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 06:30:31', '-1', 'PAL21081705243');
INSERT INTO `kh_order_info_copy1` VALUES ('a638ed9d-d60f-4a53-963a-4534cc10f5ce', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:15:47', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a6ee2038-3045-42ae-9b6c-90b546b029bf', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 03:50:33', '-1', 'PAL21081604317');
INSERT INTO `kh_order_info_copy1` VALUES ('a739f4eb-cc67-4b99-bf43-21a356625b4b', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 03:50:30', '-1', 'PAL21081701851');
INSERT INTO `kh_order_info_copy1` VALUES ('a796db93-c953-4723-b61c-86ba582ceb84', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:31:50', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a7e04d22-61be-472b-aec6-7f0413f2bec2', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:17:55', '-1', 'PAL21081424775');
INSERT INTO `kh_order_info_copy1` VALUES ('a7e7c3b0-fecf-4e6f-a63a-f5dfb03609ce', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 04:15:42', '-1', 'PAL21081503143');
INSERT INTO `kh_order_info_copy1` VALUES ('a81e4c4a-c1ee-4729-a392-007b22fe70c7', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 01:44:18', '-1', 'PAL21081626718');
INSERT INTO `kh_order_info_copy1` VALUES ('a8208eca-17ea-4b29-ae9e-7694ebcf4ae0', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 06:18:57', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a821df6e-63e1-4f19-a26a-b9a6f670cd59', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:05:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a93b1430-4b11-4e41-8629-31a0eb2f050e', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:50:20', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a9529392-1419-4ca6-9d4a-4318d2b409a3', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 02:00:12', '-1', 'PAL21081500582');
INSERT INTO `kh_order_info_copy1` VALUES ('a99c7da9-ac02-46de-b694-02ed066efcb6', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 22:53:15', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a99ff9b0-ff68-4a61-98d1-5d370ce5507c', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 18:13:13', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a9a9c3ce-19c6-4b6a-86f0-7c0c5ff9db65', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 23:11:51', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('a9c23420-6203-478d-b10b-2846907dec29', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 21:43:03', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('aa434b0b-e117-49ad-b1fc-f1ba5c908f94', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 02:49:22', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('aa7feb69-84d6-4e63-98ea-097c2d9c8311', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 09:30:10', '-1', 'PAL21081610728');
INSERT INTO `kh_order_info_copy1` VALUES ('aae77028-6324-414d-a3d9-09f4401ef520', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:30', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ab04f29e-08a0-4b42-a9b1-7cdff0714604', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 17:26:20', '-1', 'PAL21081607938');
INSERT INTO `kh_order_info_copy1` VALUES ('ab19ecc2-353d-441c-a0ac-5d48b3be6ba7', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 04:55:26', '-1', 'PAL21081903398');
INSERT INTO `kh_order_info_copy1` VALUES ('ab2aebb3-5fc7-441f-b896-5dad36427b11', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 07:42:16', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ab338720-bdbf-4348-9924-5f919a7f4315', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 16:00:29', '-1', 'PAL21081915344');
INSERT INTO `kh_order_info_copy1` VALUES ('abe539ad-6f98-4b13-84df-b5337406ac3a', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 06:08:28', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ac6bc2e1-a352-413a-bac7-76f0c9b8acba', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 01:35:44', '-1', 'PAL21081901680');
INSERT INTO `kh_order_info_copy1` VALUES ('ac706624-a23b-408e-b2f6-d9b96fb9c318', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:00:20', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ac7715f5-c01f-4ba3-9c17-decef5f8489e', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 00:39:21', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ad848991-cc95-4dcc-9cf0-67e69b762d65', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 23:32:17', '-1', 'PAL21081725581');
INSERT INTO `kh_order_info_copy1` VALUES ('ada95832-7702-450a-8488-571ec27ab3f1', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 10:30:31', '-1', 'PAL21081509795');
INSERT INTO `kh_order_info_copy1` VALUES ('ae50c2a4-930e-4cb7-b7cb-6ff1bff2eece', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 19:51:47', '-1', 'PAL21081520625');
INSERT INTO `kh_order_info_copy1` VALUES ('aea6c506-6087-494c-a90c-3a5f31d03d0d', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 00:52:56', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('aef010dd-4333-4847-939e-4e814c3562ea', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 17:14:38', '-1', 'PAL21081617193');
INSERT INTO `kh_order_info_copy1` VALUES ('af228a50-e636-4087-afa8-a0ecfea0aa6d', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 07:30:00', '-1', 'PAL21081704737');
INSERT INTO `kh_order_info_copy1` VALUES ('afa09bec-0b01-45de-8df9-96d0e0458fab', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 22:10:31', '-1', 'PAL21081723658');
INSERT INTO `kh_order_info_copy1` VALUES ('afb185b0-f97e-4149-8eb4-1cbf8775eb5b', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:41:59', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b00b7870-d94b-4ce0-969d-43eebfcaf0bf', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 12:08:28', '-1', 'PAL21081811781');
INSERT INTO `kh_order_info_copy1` VALUES ('b00f540d-d153-4cb9-a235-51fc0cea5839', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 15:47:18', '-1', 'PAL21081715997');
INSERT INTO `kh_order_info_copy1` VALUES ('b011cf7c-e822-48ca-bdb3-f443a3f4f67f', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 03:30:00', '-1', 'PAL21081600935');
INSERT INTO `kh_order_info_copy1` VALUES ('b01fb250-8686-4406-b111-e0d85d5f34d3', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 03:58:02', '-1', 'PAL21081902704');
INSERT INTO `kh_order_info_copy1` VALUES ('b03fb69b-2488-4f22-9847-3d0a285cd458', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:04:56', '-1', 'PAL21081515247');
INSERT INTO `kh_order_info_copy1` VALUES ('b0970f7e-2dc2-42d8-bd04-fa28191f1360', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 07:39:22', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b0b9dc5d-fd25-4974-aad7-87f08e06c98d', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:12:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b0dc66f7-f7dd-40a9-973a-2b34843a0b7d', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 11:56:55', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b12c83c5-0349-4033-892a-224e5029450c', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 06:43:45', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b1c09650-0f0a-4b0d-9166-943daf79d225', 'F9WC-13-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 11:50:59', '-1', 'PAL21081809667');
INSERT INTO `kh_order_info_copy1` VALUES ('b21bdb33-3682-4545-8d0c-33638963d764', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 07:55:01', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b245a718-fc19-41df-b408-9649a527ef0e', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 12:57:26', '-1', 'PAL21081711374');
INSERT INTO `kh_order_info_copy1` VALUES ('b268a9a2-fab6-496b-ac30-9609e2195a64', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 03:45:55', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b29bebb3-0631-4ff6-91d2-8e9a05f9dbf3', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 06:41:27', '-1', 'PAL21081905515');
INSERT INTO `kh_order_info_copy1` VALUES ('b2d3fe90-8df7-4ffc-9e64-2c0a591acdbc', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:32:23', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b2fd4fd0-bd72-4a97-92c8-8df3c2e16c56', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 04:13:36', '-1', 'PAL21081800956');
INSERT INTO `kh_order_info_copy1` VALUES ('b3331469-4705-4ae3-8242-d036bc0d4310', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 21:29:42', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b370b0b5-cda3-46a6-a91b-c88eb4c537a3', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 04:05:20', '-1', 'PAL21081804637');
INSERT INTO `kh_order_info_copy1` VALUES ('b3f87c42-d882-4de7-a089-4c1ac7abbecf', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 23:30:12', '-1', 'PAL21081825401');
INSERT INTO `kh_order_info_copy1` VALUES ('b470bf22-694a-4456-a70c-980732a29b27', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 06:33:10', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b4a7f37c-2dec-4098-bf09-ef3c72db96fa', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:14:18', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b51d0c78-c4c5-47f4-bcb8-9bef111213f4', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:05:43', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b54a415f-b0e5-4f06-b984-498a465bff32', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 14:31:17', '-1', 'PAL21081714406');
INSERT INTO `kh_order_info_copy1` VALUES ('b60b4d7d-a3d1-4b5e-a458-1acaf8b7e36a', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:42:58', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b6329a7b-95c3-4781-8d7b-bb03f2a6ede2', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 11:56:06', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b6520208-b484-4894-a3a0-dd6d51e3bfd2', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 21:40:56', '-1', 'PAL21081723102');
INSERT INTO `kh_order_info_copy1` VALUES ('b68a7b9e-1baa-4dac-b3f9-1abe2ad6cf4e', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 19:46:02', '-1', 'PAL21081620403');
INSERT INTO `kh_order_info_copy1` VALUES ('b6ba8e42-ba85-4de7-8bc4-c1080cbae2c5', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 09:38:54', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b75d5ea4-bc87-41e7-81f1-301d8e762b7e', 'F9WC-3-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 08:51:28', '-1', 'PAL21081806722');
INSERT INTO `kh_order_info_copy1` VALUES ('b787089c-0aaf-4bae-b30c-a2a32a301e12', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:53:48', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b7cba976-b6af-4926-ae13-77ac68ddf361', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 01:12:24', '-1', 'PAL21081700031');
INSERT INTO `kh_order_info_copy1` VALUES ('b7df6e18-d9bd-4b96-ba20-c32ba33b52e5', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 22:29:52', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b7ed12c1-bb30-4362-8976-b25f63fa32f5', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 04:41:02', '-1', 'PAL21081505018');
INSERT INTO `kh_order_info_copy1` VALUES ('b80f7f61-1e46-4ab7-865a-73303f82fe22', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:15:04', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b821ed0a-3f08-4ac4-9b07-a26bcbebe244', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 19:51:04', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b82a345b-b371-4e24-8ba3-305e8546b3a9', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 12:37:55', '-1', 'PAL21081912322');
INSERT INTO `kh_order_info_copy1` VALUES ('b8387b57-6b49-42d2-8c68-42b086b99f6d', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 04:41:03', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b89add67-eb93-45d2-bcd0-27075ff30034', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 02:56:06', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b89d006e-df3c-4538-a09f-14ec6539bf6f', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 16:54:53', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b8b9a6c1-c18c-474d-ae0f-9e32961be1ec', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 08:27:02', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b8d3e8a9-6ca2-4aff-bb08-fb9e059f3704', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 04:17:04', '-1', 'PAL21081603008');
INSERT INTO `kh_order_info_copy1` VALUES ('b8d95509-801a-43c0-9b25-34270f2c5e02', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 00:01:33', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b9660a28-cffc-43b7-b7f5-32ee8810e4aa', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 11:31:53', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b98a3efc-f8c6-42af-8f85-00d8b954696b', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 22:30:56', '-1', 'PAL21081724258');
INSERT INTO `kh_order_info_copy1` VALUES ('b9af424f-c237-4bc7-81f8-a530e3f92b34', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 17:32:41', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b9c19ec7-5db1-49d8-8c51-b5b977e21df8', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 03:19:30', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('b9dc3094-e6e2-484e-ad63-1f807bf905ac', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 00:35:33', '-1', 'PAL21081625898');
INSERT INTO `kh_order_info_copy1` VALUES ('ba1333a6-a02f-4c27-9f23-f2ffd6a14288', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 00:52:09', '-1', 'PAL21081526609');
INSERT INTO `kh_order_info_copy1` VALUES ('ba308d90-2925-4f19-beae-2a6a713b020f', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 13:20:58', '-1', 'PAL21081614886');
INSERT INTO `kh_order_info_copy1` VALUES ('ba7d3eb9-346d-4f7d-acd2-978ea3edd5a5', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 20:26:53', '-1', 'PAL21081620584');
INSERT INTO `kh_order_info_copy1` VALUES ('baaee09b-ec8f-40c7-88f7-807036abf180', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 17:16:36', '-1', 'PAL21081918570');
INSERT INTO `kh_order_info_copy1` VALUES ('babf5134-2275-47fc-83cd-682932276700', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 14:46:06', '-1', 'PAL21081614170');
INSERT INTO `kh_order_info_copy1` VALUES ('bac376c4-4e46-40b5-89d0-15670761e495', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 16:30:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bb20b141-de38-4518-b5b8-cd05cbb612bc', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 15:04:21', '-1', 'PAL21081812785');
INSERT INTO `kh_order_info_copy1` VALUES ('bbd273ea-ad88-4489-aada-61a454352f12', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 17:53:23', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bbebdbfb-c313-45ae-8e81-6bb09f57dc04', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 16:54:50', '-1', 'PAL21081616905');
INSERT INTO `kh_order_info_copy1` VALUES ('bd5f4a82-9e3d-4e80-8f07-64b288210427', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 13:21:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bd6ad3d2-ab30-47ff-b225-f20b4b2fbaec', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:49:47', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bda2b8a6-3efa-4e26-8466-c10416bf5d22', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 05:42:21', '-1', 'PAL21081606408');
INSERT INTO `kh_order_info_copy1` VALUES ('bdd3856a-9cf4-44ad-90f2-ac5bb1dd98e3', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 13:54:07', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bdde3a28-8d68-4cb2-9493-03d148903909', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:37:42', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bdf2419a-8f92-4f74-bd14-f408427d1a02', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 02:38:40', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('be037347-c533-4d2a-958b-656f8a3f729e', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 05:22:54', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('be1c9327-4a22-4eac-b64b-1c3077388e98', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 16:43:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('be2fee6e-8e63-4f33-b6c6-40bfc1787994', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 16:15:25', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('be4768ba-c933-4287-8b00-851480f4f55d', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 14:14:24', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('be570f70-8e57-4d84-9d52-42518cb06471', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 08:43:34', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('be9daf40-3cdf-41ed-867e-41bcf9f2119a', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 22:39:09', '-1', 'PAL21081724412');
INSERT INTO `kh_order_info_copy1` VALUES ('bec10b56-ce42-4807-9aa6-7e53449eabc9', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 02:01:28', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('befd49f6-8459-4913-9934-9a2de3d4a2f2', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:52:37', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bf5db249-1d98-4ba1-834a-963ec355b6e4', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 18:04:06', '-1', 'PAL21081718984');
INSERT INTO `kh_order_info_copy1` VALUES ('bf60f46f-5619-44d3-a566-cbaf7121e23f', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:02:34', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bfbb29bc-12c0-4db9-b18b-2ca2b10f1acf', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 18:48:59', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bfc3ea7a-33fc-4ba5-b571-a7f587b4aba7', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 00:59:02', '-1', 'PAL21081727331');
INSERT INTO `kh_order_info_copy1` VALUES ('bff04ae8-ae35-47de-8009-90d2f6a11a3b', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 16:09:13', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('bffa8527-4d40-41df-a9eb-b86f858a0f65', 'F9WC-13-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 07:08:41', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c087a683-14f7-4014-b6ce-a2dbfdc14846', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 12:32:45', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c0afb32d-b46b-4306-aa08-7e5f300f85b9', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 08:50:34', '-1', 'PAL21081507740');
INSERT INTO `kh_order_info_copy1` VALUES ('c0b912bb-82ab-43d4-b888-1944ed79648f', 'F9WC-5-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 06:04:37', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c0c4d695-a2cd-4fa5-ae67-0666b349cf70', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:29:03', '-1', 'PAL21081425446');
INSERT INTO `kh_order_info_copy1` VALUES ('c0cde1cd-d1c6-4f09-b2e6-8f85073e0db9', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 00:46:36', '-1', 'PAL21081727285');
INSERT INTO `kh_order_info_copy1` VALUES ('c13b0f81-6836-4e97-8c48-afdb76faeb2f', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 07:23:53', '-1', 'PAL21081606730');
INSERT INTO `kh_order_info_copy1` VALUES ('c2148e61-c6f7-4064-b585-a940813f7a5b', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 15:40:59', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c2708bd0-e429-4c07-8880-78b37ec5821e', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:38:57', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c285d638-7fe7-47d8-8fdb-9c3f31125e17', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 17:57:20', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c28a53d0-f88d-4baf-abcf-1c60db9d1272', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 19:15:54', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c2b44412-1a4b-4254-872a-f48971f2d269', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 17:52:01', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c2dd94b9-5d13-4025-a031-ef51a33bd95c', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 21:44:20', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c2e392f0-0c68-4ffd-b38e-dbf1ca589b13', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 01:02:16', '-1', 'PAL21081701059');
INSERT INTO `kh_order_info_copy1` VALUES ('c340eae4-0ae1-4e13-abea-4b42bbcc680f', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 23:14:14', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c36c058a-09ab-43df-8f24-1d442a07ced3', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 11:07:20', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c39f00b0-7488-4375-ae69-29c70a21ed2c', 'F9WC-13-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:58:58', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c410c193-acce-499d-8ec7-113be9077f15', 'F9WC-11-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 23:11:36', '-1', 'PAL21081726884');
INSERT INTO `kh_order_info_copy1` VALUES ('c4161cb9-ba04-4fd0-a31c-052bf36a2db3', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 17:28:25', '-1', 'PAL21081617471');
INSERT INTO `kh_order_info_copy1` VALUES ('c42f9f5a-42ba-4723-987d-054aa063e5d1', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 11:35:59', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c499eb17-f38a-4691-9235-8809e31e07c1', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 13:14:42', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c4d2081a-0ebb-4115-89d1-975a870cc5dd', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:51:07', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c50bb472-5c03-435a-879c-3b1078604dc9', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 15:50:41', '-1', 'PAL21081914505');
INSERT INTO `kh_order_info_copy1` VALUES ('c56ac1d3-0aa2-4fc5-a5aa-285bc82bbef7', 'F9WC-12-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:37:36', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c58cb8db-eba6-4c81-8aa4-ab5f04ed9d7f', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 04:17:08', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c5af086e-8894-413c-9976-01735313f290', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 00:17:56', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c5cb2b2e-d858-4bcb-90fd-cfa07287ea64', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:32:12', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c5efe816-7eb5-4749-8e0a-fe05c70b6d7a', 'F9WC-12-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 23:25:00', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c61db943-3e63-4043-8c83-890d265127cd', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 10:55:38', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c63b556e-1516-4ab0-ac32-185fd5b89686', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:10:23', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c64a2a34-f9bd-4f7e-9e66-4bac9cc3477f', 'F9WC-1-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:10:32', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c678ad14-6720-47c1-b14a-0ae0032aa3d7', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 10:39:41', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c67fba83-3b24-4fba-aa50-403905f33e12', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 11:35:27', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c6ac50c1-f889-4980-8b3f-fcf53c6c0f7b', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 17:49:45', '-1', 'PAL21081518347');
INSERT INTO `kh_order_info_copy1` VALUES ('c6d45f4b-1adc-4c3a-86c8-665b9b1555ce', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:24:25', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c6e21683-70d3-4a01-92a4-f86bab6b4a4a', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 11:33:11', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c70f0ce7-2449-48c5-8e46-3c5b98089b90', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 05:55:38', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c710d629-e7c0-4d05-9bc4-251405baa20f', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 15:14:40', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c7414cce-b27f-4f97-880d-b54b75f4eeac', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 06:22:29', '-1', 'PAL21081504810');
INSERT INTO `kh_order_info_copy1` VALUES ('c7901635-d2cb-4cf2-8031-d3453f9b5ab8', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 15:41:47', '-1', 'PAL21081513659');
INSERT INTO `kh_order_info_copy1` VALUES ('c845ba69-7b49-4ccb-a91c-205f86801bb3', 'F9WC-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 00:52:29', '-1', 'PAL21081726880');
INSERT INTO `kh_order_info_copy1` VALUES ('c93ef6ac-9f3b-4677-af3c-73b465ae2083', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 23:57:10', '-1', 'PAL21081527250');
INSERT INTO `kh_order_info_copy1` VALUES ('c940d748-f507-43e8-a2ac-c5648ac12713', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 17:49:49', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('c98a2c09-c3cc-4d9e-80a5-9ef69cd774c7', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 14:57:20', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ca08dacf-3cda-49c6-813b-9e743c29105b', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 02:23:19', '-1', 'PAL21081500780');
INSERT INTO `kh_order_info_copy1` VALUES ('cabdd828-97e4-4c1b-b23b-6b1eb9962d83', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:37:28', '-1', 'PAL21081500514');
INSERT INTO `kh_order_info_copy1` VALUES ('cac0c2cd-8ea8-4d2f-ab88-9224515ddbda', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 03:20:03', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('caebdfa2-af7c-41b2-a31f-f9942bed3c90', 'F9WC-12-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 00:17:54', '-1', 'PAL21081424424');
INSERT INTO `kh_order_info_copy1` VALUES ('cafa427a-83d4-488e-bdb8-abafe8bb84d9', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 19:43:00', '-1', 'PAL21081720657');
INSERT INTO `kh_order_info_copy1` VALUES ('cb038f05-2e60-443d-8d74-fac78508104e', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 09:12:47', '-1', 'PAL21081508646');
INSERT INTO `kh_order_info_copy1` VALUES ('cb1f4d83-d32d-43d7-a54c-e1804951f1e9', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 12:01:11', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cb56faa7-3ccd-4818-808a-04fa6d76380f', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 07:26:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cb757076-b3a3-4be8-ad8a-5807183faa27', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 08:38:28', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cbb2097b-69ee-4cd5-8411-6c7ae2346736', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:02', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cbe871e3-9c38-486b-a92d-f95d837aea0d', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 07:52:24', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cc123b3f-0f6d-48a5-88e6-fe8520554034', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 19:52:55', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cc23afd4-023f-4e98-bb0a-1508a072620b', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:14:03', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cc2b8511-b5ad-456c-b362-2ada65fb7640', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 18:39:58', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cc7ba433-df84-4f80-a523-ad71e2c8c555', 'F9WC-5-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 06:26:11', '-1', 'PAL21081505335');
INSERT INTO `kh_order_info_copy1` VALUES ('cca16e33-fb9f-4cf3-a24a-f19e9d48ea33', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 07:42:02', '-1', 'PAL21081506645');
INSERT INTO `kh_order_info_copy1` VALUES ('ccd77122-853f-4a07-bc21-cccd87afd26d', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 15:59:53', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cd388d0d-c538-4963-8c41-d9f2de05594e', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-14 21:15:16', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cdf73192-8ec0-44df-8bb6-9ee3ca3a47e4', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 18:58:05', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ce0c0826-0613-4694-9c21-356776e8240d', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 18:58:20', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ce17f2de-832a-42ba-a670-bfb2f4cbd7d7', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:18:49', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ce8a9c2c-d725-4c86-8944-34e1311b576f', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 08:45:45', '-1', 'PAL21081608149');
INSERT INTO `kh_order_info_copy1` VALUES ('ce8e0217-e7c0-459a-a821-06e2f5173909', 'F9WC-4', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 04:46:55', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cedb2e4d-7e07-4e6c-8364-ee9515f88626', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 12:10:25', '-1', 'PAL21081711684');
INSERT INTO `kh_order_info_copy1` VALUES ('cf504c6e-367f-40a9-90b5-5767985f6053', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:58:03', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cf69e68a-6b3e-4aa4-b7e9-4becf3dcda3e', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 17:15:03', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('cfebdd47-399d-426b-9189-969798e98dcc', 'F9WC-4', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 10:07:06', '-1', 'PAL21081809101');
INSERT INTO `kh_order_info_copy1` VALUES ('cfeca1a3-8238-4855-b3a1-a16f8ee5a7e4', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 03:27:22', '-1', 'PAL21081602410');
INSERT INTO `kh_order_info_copy1` VALUES ('d01b08ad-ec21-4a32-8405-afc571c7ec8f', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 06:19:11', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d01d799a-1109-4fb4-b493-0f34cc47c1c8', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 05:32:13', '-1', 'PAL21081903702');
INSERT INTO `kh_order_info_copy1` VALUES ('d022f642-4b2e-48af-b467-de6862bd8478', 'F9WC-12-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 12:11:41', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d097f47f-4c6f-4141-8931-1b46baf6b490', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 20:03:20', '-1', 'PAL21081620212');
INSERT INTO `kh_order_info_copy1` VALUES ('d097fc0b-248f-440b-bbd6-c230448927f2', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 13:45:40', '-1', 'PAL21081513245');
INSERT INTO `kh_order_info_copy1` VALUES ('d09a87f3-5da4-446c-b96d-5297914cb605', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 11:56:40', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d0fc7d9b-2f5c-4c3e-8524-a338e9b206e3', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 00:06:24', '-1', 'PAL21081825672');
INSERT INTO `kh_order_info_copy1` VALUES ('d10f4a73-980a-42aa-b550-85af58b4eace', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:03:28', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d148359e-4add-481a-b648-a0621dbd84ce', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 13:15:19', '-1', 'PAL21081912508');
INSERT INTO `kh_order_info_copy1` VALUES ('d14b8bda-1d2b-42f7-b4af-145d6c4a516f', 'F9WC-13-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 12:31:00', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d167cb54-dbc5-4c45-9990-7c940926b47f', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 09:05:31', '-1', 'PAL21081808109');
INSERT INTO `kh_order_info_copy1` VALUES ('d1b40d0a-3992-45b9-b1b8-cb213c30bd97', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:29', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d230247e-6385-49fb-b3c3-73f1ac341abd', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 09:22:39', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d2933f07-ad0b-4ca9-962a-3cfc89ca94a4', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:51:37', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d297a203-b561-4b83-b6cb-633dfe93d21c', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 22:11:32', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d2db7650-8672-4ac2-a465-193099d88efc', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 11:10:48', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d325fe15-5bc8-49c6-bfb5-50a9c06f871c', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 15:03:57', '-1', 'PAL21081916288');
INSERT INTO `kh_order_info_copy1` VALUES ('d350183a-dddf-4acd-a83a-6635c27438e4', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 13:06:08', '-1', 'PAL21081912431');
INSERT INTO `kh_order_info_copy1` VALUES ('d351b871-6050-4833-af9b-ac28810bf895', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 11:26:37', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d36823f1-a072-40d1-a57e-e008fd65945f', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 12:11:40', '-1', 'PAL21081710790');
INSERT INTO `kh_order_info_copy1` VALUES ('d3a5dbfb-591e-4d40-9e87-07d4aeedb470', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 22:03:01', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d3b468b5-9e4c-43c1-864d-14883ae38bc4', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 01:32:09', '-1', 'PAL21081500058');
INSERT INTO `kh_order_info_copy1` VALUES ('d3b5fe69-aaac-4b65-acd7-d462bd3f14e8', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 10:18:41', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d464b5ad-5ef8-4f04-a0a1-51670deef044', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 22:27:20', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d476bce5-9d96-45a2-bfd0-44a3549eb941', 'F9WC-13-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 21:29:44', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d48327e0-6133-4f93-b13d-bdd29936ec2a', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 22:11:27', '-1', 'PAL21081723687');
INSERT INTO `kh_order_info_copy1` VALUES ('d492bb27-3b37-484a-b4a3-9c8aa147a2ee', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:42:45', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d4b872cf-46ea-4627-b4e6-ae2bf76bdcf9', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 22:59:36', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d4cae3f8-b9ad-4013-90d5-de29a3b968cb', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 05:32:15', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d4ee9f68-428a-4f14-ae5f-50d43830d2a4', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 20:16:05', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d4efc952-07b4-4805-b796-71a988bfe9f0', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:29:39', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d50c5b98-9335-4999-8f3d-8624f12c23a9', 'F9WC-11-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 01:55:23', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d52a2c75-b36d-49ae-ae73-d69d8d505d8b', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 03:31:30', '-1', 'PAL21081903716');
INSERT INTO `kh_order_info_copy1` VALUES ('d54fe3d4-8fd4-45cc-a721-aaccd401955a', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 10:14:32', '-1', 'PAL21081909073');
INSERT INTO `kh_order_info_copy1` VALUES ('d551a9ae-3e99-4205-8acf-6f4e0ef30bb4', 'F9WC-1-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:29:52', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d5614b1e-9885-4cf9-b6d9-f6ffb3e987fa', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:49:34', '-1', 'PAL21081900998');
INSERT INTO `kh_order_info_copy1` VALUES ('d574bfa9-f361-4bb4-9d8a-55a1fa3f7481', 'F9WC-3-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 09:43:48', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d5b2a070-0c40-4d16-acde-9317dc227f8e', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 07:10:00', '-1', 'PAL21081505712');
INSERT INTO `kh_order_info_copy1` VALUES ('d5b42f1f-af66-447c-b23d-8fd607fad1c1', 'F9WC-12-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-16 10:20:19', '-1', 'PAL21081608330');
INSERT INTO `kh_order_info_copy1` VALUES ('d5f37676-40c1-4906-bd5c-13a968b7b262', 'F9WC-3-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 18:00:32', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d610c562-dde6-4d11-bc41-314333228f96', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 23:52:37', '-1', 'PAL21081825863');
INSERT INTO `kh_order_info_copy1` VALUES ('d62ba554-bd2c-453e-a7de-74f560587a7f', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 05:16:00', '-1', 'PAL21081903106');
INSERT INTO `kh_order_info_copy1` VALUES ('d64baffa-e02a-4fb6-964d-fea67023476a', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 10:50:42', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d65e47bd-48b2-483c-807c-ff7a51d95bde', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 08:38:37', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d66729fe-d786-4b45-ad24-50dcb68e0c25', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 13:19:12', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d67770d3-3b0c-455c-aee8-5efa966d6745', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 14:31:17', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d6965634-bc53-41d3-a7ea-857279bc51cf', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 13:46:47', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d6bdfed9-72f4-44a9-884f-88de5a606997', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-16 21:32:04', '-1', 'PAL21081622356');
INSERT INTO `kh_order_info_copy1` VALUES ('d72e204b-6711-4a68-bc23-793d78a8427a', 'F9WC-13-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 05:15:18', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d730ea37-3b62-40c2-b0a1-6bdece573ecf', 'F9WC-1-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 02:49:37', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d7706f96-ccbf-4cd3-875c-49b9dfc5cc47', 'F9WC-12-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 06:24:22', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d79b89fe-2f18-4449-ac94-12f6b39e29ed', 'F9WC-3-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 08:51:28', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d7ae39f1-4536-4664-8821-f5f4671e459c', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 03:50:29', '-1', 'PAL21081703385');
INSERT INTO `kh_order_info_copy1` VALUES ('d7c5f9e5-fe3c-4472-8560-a9c565912d53', 'F9WC-12-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 05:43:08', '-1', 'PAL21081603161');
INSERT INTO `kh_order_info_copy1` VALUES ('d7e02bab-ab08-468c-9f7c-169209b46be8', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 00:23:05', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d89f6405-01fe-43f2-90d1-171599a31b52', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 19:31:17', '-1', 'PAL21081720525');
INSERT INTO `kh_order_info_copy1` VALUES ('d8cec5cb-a2e5-4308-a2f7-d19c1e69633f', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:13:27', '-1', 'PAL21081900557');
INSERT INTO `kh_order_info_copy1` VALUES ('d8d17550-0cfe-49d3-a9c6-fecc7b51e56d', 'F9WC-13-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:54:19', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d8d2da4d-174c-4feb-8887-871aef171164', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 01:50:19', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d9193350-1492-42ff-ab08-9e1447667c1d', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 15:54:04', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d9202b1b-3349-440a-8335-6dddcdae4813', 'F9WC-11-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 10:13:57', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d924e29d-164e-47a5-af36-9118a9a713d7', 'F9WC-5-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 12:56:06', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d93608d5-c878-4912-98e3-49b0630ac13b', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 10:33:21', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d9583159-bfb2-4736-90dd-eef03741e673', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 13:12:57', '-1', 'PAL21081326089');
INSERT INTO `kh_order_info_copy1` VALUES ('d97d5589-df15-4fc0-8172-f77a3da27c19', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 15:54:53', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d9a956f2-299e-4eb8-8fc5-8bf971d8829d', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 05:25:11', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('d9e114cf-c3c5-494d-80b5-f5e45776e6bf', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 13:19:07', '-1', 'PAL21081712920');
INSERT INTO `kh_order_info_copy1` VALUES ('d9fd9cac-e4c3-4089-8d8a-f1d2faa096a6', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 00:39:18', '-1', 'PAL21081726805');
INSERT INTO `kh_order_info_copy1` VALUES ('da9a2be0-9584-47e5-8ab2-55ad619e3fc4', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 05:38:21', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dab785ee-246f-441e-9c93-2aa4a15ceef5', 'F9WC-3-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 17:26:24', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dbaf4b0f-521d-45ba-832d-0b153d0512ae', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:47:41', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dbc27f8f-7836-4576-aa8c-67e88796d0d6', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 17:51:58', '-1', 'PAL21081818411');
INSERT INTO `kh_order_info_copy1` VALUES ('dbc8b924-fde0-40ec-bc9c-ff120d12c4de', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 20:10:15', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dbd69065-e3a7-4cae-a29d-e4ffef8c874d', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 20:03:47', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dc32419f-041f-4200-904e-4c384bda3044', 'F9WC-13-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 05:34:31', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dc3ab91e-3b57-41b7-b8e9-d0fce3d36d08', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 20:26:56', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dd1e7186-e7ce-4df5-9480-6a1c986792ff', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 06:01:08', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dd697810-4c60-47d1-b3ea-30f8579e5b13', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 13:01:54', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dd6c070c-5ffc-4978-aee5-acb44f978db9', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 11:50:28', '-1', 'PAL21081910418');
INSERT INTO `kh_order_info_copy1` VALUES ('ddbfc61d-947c-4387-a364-bcc0994a5937', 'F9WC-1-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:43:34', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ddfbb32b-1eb5-463d-975e-1d011645d13d', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 08:49:14', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('de545ad9-7782-466d-99b5-295f21c2ed78', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 13:37:39', '-1', 'PAL21081813692');
INSERT INTO `kh_order_info_copy1` VALUES ('dee5c3b2-a43a-49e2-9699-f5536dc43e36', 'F9WC-11-2', '', '2', 'OVER', 'GOODS', 'CARRY', '2021-08-17 18:24:20', '-1', 'PAL21081721047');
INSERT INTO `kh_order_info_copy1` VALUES ('deea7127-4550-4ea5-a329-9f3896343896', 'F9WC-2', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 11:38:44', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('dfc2773d-7295-4755-9936-c7278c26842d', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 07:19:58', '-1', 'PAL21081806473');
INSERT INTO `kh_order_info_copy1` VALUES ('e014bcf0-f7a9-4a6b-87df-ff609a10824b', 'F9WC-11-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-15 06:43:06', '-1', 'PAL21081507305');
INSERT INTO `kh_order_info_copy1` VALUES ('e07bdcb4-5748-496a-bb99-14ac02b56936', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 07:55:50', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e07e1376-d183-4792-83a4-85192c831f5c', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 20:27:09', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e09a4150-0e7b-4f6b-b419-4f6d0bf174ea', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 17:50:50', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e10b0017-b7fc-47f1-923d-84798cd0d23a', 'F9WC-1-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-17 07:25:54', '-1', 'PAL21081705937');
INSERT INTO `kh_order_info_copy1` VALUES ('e1170dab-4380-4586-bf96-388d0bf0aa58', 'F9WC-3-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 02:38:17', '-1', 'PAL21081526670');
INSERT INTO `kh_order_info_copy1` VALUES ('e1248079-c995-4dce-94ee-8246ad49820e', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 03:50:30', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e1367270-81b3-4fa3-93a9-6be934f6aa95', 'F9WC-5-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-16 18:58:02', '-1', 'PAL21081619356');
INSERT INTO `kh_order_info_copy1` VALUES ('e15d902a-bc78-40d9-b1f7-ca0635fbe6ea', 'F9WC-5-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 13:33:10', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e2442c6e-df9b-4789-bcc0-46db88fd3718', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 14:32:16', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e2c037a9-4d3e-414a-86c8-3520a0790c1a', 'F9WC-11-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:56:14', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e2cf4f5d-bffb-4cab-910e-d8a68a496aaa', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 17:32:39', '-1', 'PAL21081718547');
INSERT INTO `kh_order_info_copy1` VALUES ('e2f7c3a7-56a5-43a8-a5a5-4253e5d4cc62', 'F9WC-1-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-17 04:12:30', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e301ca6f-ec06-4412-91bf-0429f685aa73', 'F9WC-3-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-16 02:38:15', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e3020d8a-011c-4019-84f2-8aa657a4736d', 'F9WC-4', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 16:29:05', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e303ed7c-456b-4a4d-a595-25c5f1e7ea3a', 'F9WC-5-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 00:21:14', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e375c31d-ff23-4616-96d6-59ea967c408f', 'F9WC-5-1', '', '2', 'OVER', 'TRAY', 'CARRY', '2021-08-15 04:15:46', '63', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e37f4289-9b09-4429-b695-f0b283ea8d23', 'F9WC-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 06:18:57', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e3be6254-9e14-47c0-9bd3-6aae14ec91bc', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 12:13:41', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e40179b0-5674-4fcd-9802-a5378d66f718', 'F9WC-11-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 00:17:55', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e417d7ee-25a0-4aab-bbd6-f3535ee86438', 'F9WC-12-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-14 19:09:16', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e54eb662-5a68-4acc-96d1-15fcb7ab7ce7', 'F9WC-11-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 08:43:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e5a4395e-1c0b-42f2-bcde-68a1647363a0', 'F9WC-5-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-17 20:19:30', '-1', 'PAL21081721626');
INSERT INTO `kh_order_info_copy1` VALUES ('e5a9a996-5ff8-434f-85ae-1a356b1ef49d', 'F9WC-2', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 22:39:11', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e5ca0edb-66e2-4adc-948c-2c2a48af842b', 'F9WC-5-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 12:56:04', '-1', 'PAL21081512608');
INSERT INTO `kh_order_info_copy1` VALUES ('e68cbbf5-58cc-4e27-873a-57889e48e49c', 'F9WC-2', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 12:01:24', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e6f93e9c-250e-4fa5-b3d3-a60322b74185', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 15:02:27', '-1', 'PAL21081914112');
INSERT INTO `kh_order_info_copy1` VALUES ('e743e37a-4260-47db-9893-2787ad83b544', 'F9WC-11-1', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 16:10:28', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e76279f3-c78a-49d9-a3d6-4232397ab0f4', 'F9WC-4', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 11:56:26', '-1', 'PAL21081610990');
INSERT INTO `kh_order_info_copy1` VALUES ('e76704ce-467f-4d28-88b9-5be9744c84f5', 'F9WC-1-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 17:19:13', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e784c521-8ac0-4072-a718-28ce1aa0a80f', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 00:37:29', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e7d25bd0-ac3e-4b40-859c-980488c76dc0', 'F9WC-1-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 02:23:21', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e7eb8f1b-61d7-49c7-963e-16214a8edf29', 'F9WC-3-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 03:34:25', '-1', 'PAL21081602125');
INSERT INTO `kh_order_info_copy1` VALUES ('e871eba4-763a-450b-9343-50e87c981d3c', 'F9WC-4', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 16:22:43', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e88c6a06-4a8b-4827-b33f-35eb751d14bd', 'F9WC-1-1', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 05:04:31', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e894f039-6e42-43a8-b579-aa4243ac498c', 'F9WC-3-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 17:18:50', '-1', 'PAL21081615881');
INSERT INTO `kh_order_info_copy1` VALUES ('e8a5636f-4740-43d2-a6b7-195fb2174170', 'F9WC-5-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 09:21:08', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('e8bab38d-464a-40f2-accb-05fb75ba0949', 'F9WC-4', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 22:07:39', '-1', 'PAL21081522591');
INSERT INTO `kh_order_info_copy1` VALUES ('e9f9a7f4-16c8-4bf4-b6dc-ed5e19d5a3a2', 'F9WC-12-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 15:12:10', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ea79c463-7d8b-4573-ba81-8ea19ff20203', 'F9WC-5-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 14:13:38', '-1', 'PAL21081614185');
INSERT INTO `kh_order_info_copy1` VALUES ('ea97c015-85fa-4878-ac99-599989fb92b0', 'F9WC-3-2', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 11:31:45', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('eb200ec7-f2cf-47d8-9dae-5405eb4ccd38', 'F9WC-12-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 00:56:24', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('eb3ef458-7b49-4ea6-9898-ce87c2e8802b', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 20:10:12', '-1', 'PAL21081821603');
INSERT INTO `kh_order_info_copy1` VALUES ('eb584e4e-0e1b-4f10-bc8c-9dd2010d5a34', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 06:51:36', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('eb5d6778-b337-49db-9df7-33e4cc66d282', 'F9WC-2', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 20:14:59', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('eb6848c3-fb14-4c8a-bc41-2444c9dcb7e6', 'F9WC-11-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 03:27:27', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('eba41fae-f78a-48b7-8e36-dd7fa5cf974a', 'F9WC-11-1', '', '10', 'REVOKE', 'GOODS', 'CARRY', '2021-08-18 08:58:28', '-1', 'PAL21081808801');
INSERT INTO `kh_order_info_copy1` VALUES ('ec3656dd-bf1c-45e8-88f6-3adeb852a331', 'F9WC-11-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-14 21:43:59', '-1', 'PAL21081422693');
INSERT INTO `kh_order_info_copy1` VALUES ('ec805955-1f95-43ae-960f-1958dd863a8e', 'F9WC-4', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 03:04:53', '-1', 'PAL21081501144');
INSERT INTO `kh_order_info_copy1` VALUES ('ecb29520-dffd-4a59-aec0-531b0d6bfdd7', 'F9WC-13-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 10:41:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ece736ef-7403-4cb4-896d-ade96b3548b3', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-14 18:34:04', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ed826af1-bf3e-4616-b4c7-6c0b1ab4791b', 'F9WC-3-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 09:31:41', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('edf94989-90b6-40a8-b585-27c6fbd0c776', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 12:37:58', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ee4068ec-bc68-412d-bd76-5e974aac9b2d', 'F9WC-5-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 02:09:05', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ee56b428-1f08-4d17-9bd6-25d089888c76', 'F9WC-5-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-17 10:46:09', '-1', 'PAL21081710453');
INSERT INTO `kh_order_info_copy1` VALUES ('ee5812d7-9e52-4bc7-b9a1-5d0a848005e9', 'F9WC-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 14:46:01', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ee99abc5-e674-49b4-a365-bc659ad151d3', 'F9WC-3-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 06:37:01', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('eecb96e5-b195-4f40-8533-98d1f6d06818', 'F9WC-3-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 22:45:13', '-1', 'PAL21081523666');
INSERT INTO `kh_order_info_copy1` VALUES ('eed9427a-76bd-4ba5-a158-5035ddaf8cfe', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 22:10:49', '-1', 'PAL21081823909');
INSERT INTO `kh_order_info_copy1` VALUES ('ef0cc8d0-5b62-4ebd-9451-d36b51da4f5a', 'F9WC-3-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 12:18:01', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ef0f4800-453f-4b78-b061-b000bd63021d', 'F9WC-13-2', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 07:25:09', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ef59f9c3-6ebd-47de-9195-7ec5064973ba', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-15 02:00:25', '-1', 'PAL21081500117');
INSERT INTO `kh_order_info_copy1` VALUES ('ef5ab13a-7ec0-4d14-be40-4dfd62097a92', 'F9WC-4', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 03:41:58', '-1', 'PAL21081601301');
INSERT INTO `kh_order_info_copy1` VALUES ('ef6684cf-0e91-4108-9045-432665250738', 'F9WC-1-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 03:08:44', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('efbf2db8-8a3a-491a-82a5-4652bcfcf75c', 'F9WC-5-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 14:13:42', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('efc6d7c9-542f-4a04-9c3b-fc77b6e2c5b3', 'F9WC-5-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-14 23:14:32', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('efe55115-9014-49fd-b729-a80ec5dd5bc5', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 08:43:01', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f08cb660-efbb-4e6d-9f07-4052233bdd01', 'F9WC-13-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-18 15:56:19', '-1', 'PAL21081814870');
INSERT INTO `kh_order_info_copy1` VALUES ('f0a3ee84-ef06-4781-92bc-8fe46cdc9fe9', 'F9WC-3-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 16:10:06', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f0e3612b-43d3-4f61-ae22-2cc36d7e80b1', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 21:41:41', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f139e319-1490-489c-ab1a-2e4898d6ce43', 'F9WC-1-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 07:30:11', '-1', 'PAL21081506267');
INSERT INTO `kh_order_info_copy1` VALUES ('f1658fb9-b80c-426c-aff3-c141ce68479d', 'F9WC-4', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 13:45:51', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f1a03825-d26c-4b1f-834b-a2fa5b3d4b55', 'F9WC-11-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 22:43:26', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f1aed61f-763a-41a2-b2bb-a16d40c4a54e', 'F9WC-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 19:59:01', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f1c2ba7d-1ae3-4a18-8dba-07439888e9ad', 'F9WC-12-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 07:30:05', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f1e37cf7-2a5c-4c92-a584-7de75854b405', 'F9WC-5-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 05:21:20', '-1', 'PAL21081804460');
INSERT INTO `kh_order_info_copy1` VALUES ('f2707e5d-28d8-4295-b744-2c276cd23dd0', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 02:49:58', '-1', 'PAL21081801733');
INSERT INTO `kh_order_info_copy1` VALUES ('f293f0ce-8ab7-4709-8bbb-5065bef4fc13', 'F9WC-1-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 16:15:22', '-1', 'PAL21081817133');
INSERT INTO `kh_order_info_copy1` VALUES ('f2f8780d-e701-43cf-802d-5faab345b795', 'F9WC-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 01:20:37', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f308ca40-b254-441e-a676-b67017cc1500', 'F9WC-12-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-17 01:50:24', '-1', 'PAL21081624501');
INSERT INTO `kh_order_info_copy1` VALUES ('f310b8a9-e27d-4e0d-817a-1d139a801ceb', 'F9WC-12-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 17:44:38', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f340a3f7-400c-4980-bd44-9f27ba137c9f', 'F9WC-11-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-14 19:51:56', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f381a08a-f66c-476e-b9d2-e8cc505abcdb', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 01:42:53', '-1', 'PAL21081900268');
INSERT INTO `kh_order_info_copy1` VALUES ('f38501c3-e774-4ea1-a092-6b6bfb704b0a', 'F9WC-11-1', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-18 19:57:25', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f395cc1e-d04a-4128-b699-2bb63135fd0d', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 08:34:34', '-1', 'PAL21081907445');
INSERT INTO `kh_order_info_copy1` VALUES ('f3e9eadc-0630-481a-8b96-7ccec02a4ff9', 'F9WC-3-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 13:46:57', '-1', 'PAL21081813798');
INSERT INTO `kh_order_info_copy1` VALUES ('f40a6101-d972-464a-b191-2c264b107bf8', 'F9WC-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 17:25:33', '-1', 'PAL21081818040');
INSERT INTO `kh_order_info_copy1` VALUES ('f4766754-da79-430e-818d-83f78a982321', 'F9WC-1-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 02:49:36', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f48470a0-afc5-47a7-b539-f9f24cd16a52', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 18:41:57', '-1', 'PAL21081719164');
INSERT INTO `kh_order_info_copy1` VALUES ('f4b6d2ad-b627-4de7-b369-205047f471c9', 'F9WC-11-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 16:04:06', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f4bffc2f-afd3-4732-ad2e-a0d1bea52cda', 'F9WC-1-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 17:06:52', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f50adfa6-4050-41a8-a9a6-cc9c79c51428', 'F9WC-4', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 03:05:24', '62', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f53c3726-2867-4ff2-86d2-dc72cdde657c', 'F9WC-5-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 00:17:55', '-1', 'PAL21081424870');
INSERT INTO `kh_order_info_copy1` VALUES ('f5c1098c-ed7d-43ec-85e1-e9bae8ec1011', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 14:19:36', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f624c287-63e0-45d6-85b7-3c31a9b99117', 'F9WC-4', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-18 18:30:07', '-1', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f62844e9-7276-4bba-ba62-64b35f34f824', 'F9WC-11-1', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 09:03:52', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f665dc18-9886-4a58-865e-ebcf6a429269', 'F9WC-4', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-17 01:19:30', '-1', 'PAL21081625952');
INSERT INTO `kh_order_info_copy1` VALUES ('f7181bef-3241-4348-9ca4-981a5b38d3cf', 'F9WC-4', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-18 23:39:04', '-1', 'PAL21081825119');
INSERT INTO `kh_order_info_copy1` VALUES ('f7c0dc6f-cdbd-455a-8075-67ac516c9bce', 'F9WC-11-1', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 17:09:57', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f7eff23f-c120-47a8-9bef-726763c3f68a', 'F9WC-3-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 00:17:54', '-1', 'PAL21081424011');
INSERT INTO `kh_order_info_copy1` VALUES ('f828880e-cdaa-48ab-b56d-6dd524bb7c94', 'F9WC-1-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 12:18:03', '0', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f83bb88b-76c5-48be-a9b3-6a0cfb6ff6b0', 'F9WC-13-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 18:34:45', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f84500db-366e-49dc-ac18-044a84b731ec', 'F9WC-3-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 07:08:59', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f850c14a-5d17-4a61-968a-b18e4616ff37', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 23:46:00', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('f88c0bf6-3209-4078-a5e5-f245380e207e', 'F9WC-11-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 03:31:13', '-1', 'PAL21081902188');
INSERT INTO `kh_order_info_copy1` VALUES ('f922c34b-c773-4a2e-aabd-14e64d33fe52', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 19:57:21', '-1', 'PAL21081821510');
INSERT INTO `kh_order_info_copy1` VALUES ('f93d5638-f926-46de-bca8-7a444ccda851', 'F9WC-13-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 00:10:05', '-1', 'PAL21081524378');
INSERT INTO `kh_order_info_copy1` VALUES ('f96bb639-f59f-4568-ab3a-92435b116383', 'F9WC-3-2', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 12:01:09', '-1', 'PAL21081911387');
INSERT INTO `kh_order_info_copy1` VALUES ('fa0a1a7c-f7ae-4616-8118-2035f55ea703', 'F9WC-12-1', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 07:26:46', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fa7bf891-ecf8-409a-9be0-370bf4e24d8f', 'F9WC-4', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 01:31:52', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fa7f29c4-e18e-478a-a216-71e1c6679a17', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 18:09:50', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fabeb32f-2b01-4a0b-a1a0-fa086963ecff', 'F9WC-5-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 13:46:42', '-1', 'PAL21081814182');
INSERT INTO `kh_order_info_copy1` VALUES ('fb14be41-141c-4e1b-833c-3670e33ed520', 'F9WC-1-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 17:49:06', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fb37e914-d034-462e-ab79-98c5e7938992', 'F9WC-11-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 12:42:50', '-1', 'PAL21081813199');
INSERT INTO `kh_order_info_copy1` VALUES ('fb45b92a-3bb5-4d48-b1fb-d41697afc8c8', 'F9WC-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 19:43:16', '-1', 'PAL21081619834');
INSERT INTO `kh_order_info_copy1` VALUES ('fb9902a3-6d73-454c-9b7b-ef6bd71522e3', 'F9WC-11-1', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 08:42:59', '-1', 'PAL21081604454');
INSERT INTO `kh_order_info_copy1` VALUES ('fbb7aa91-4324-46d3-a5de-028c4b89f726', 'F9WC-13-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 07:53:10', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fbd221a0-6061-4654-9493-5a67127243e9', 'F9WC-4', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 09:20:31', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fbee6f72-aecc-4f6f-8079-dcea52b01c54', 'F9WC-4', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 23:39:33', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fc0531d1-c474-4b85-a44b-44c60528ed10', 'F9WC-5-2', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-19 03:58:08', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fc0a7804-4317-476a-bbca-065d87d2de95', 'F9WC-2', '', '1', 'OVER', 'TRAY', 'CARRY', '2021-08-19 11:09:57', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fc46e8fe-421a-4238-ae9a-9665f904278a', 'F9WC-1-1', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-17 17:06:49', '-1', 'PAL21081717628');
INSERT INTO `kh_order_info_copy1` VALUES ('fc834b78-4739-4229-846e-6829b94ac8e1', 'F9WC-1-2', '', '10', 'OVER', 'GOODS', 'CARRY', '2021-08-18 03:08:41', '-1', 'PAL21081801399');
INSERT INTO `kh_order_info_copy1` VALUES ('fced1f78-3cd6-45b5-8626-0891a960275a', 'F9WC-13-1', '', '1', 'OVER', 'GOODS', 'CARRY', '2021-08-19 02:05:37', '-1', 'PAL21081827202');
INSERT INTO `kh_order_info_copy1` VALUES ('fd773671-e508-4695-89d0-57ec0d16f540', 'F9WC-5-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-15 03:51:48', '61', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fd98c8ff-91c9-41d3-b8e3-6ee2b3ee9e35', 'F9WC-5-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 08:21:36', '-1', 'PAL21081507483');
INSERT INTO `kh_order_info_copy1` VALUES ('fdadc96c-1db3-4ab2-ba94-cc050308de15', 'F9WC-1-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-15 12:18:01', '-1', 'PAL21081511090');
INSERT INTO `kh_order_info_copy1` VALUES ('fe33b816-4e64-4d47-b19c-b356fac2ac21', 'F9WC-1-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 05:54:33', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('fe53e641-57fc-4b26-8fe0-d1fac2cc22d5', 'F9WC-11-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-16 20:36:24', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('feba5197-9c65-4cf9-a2b2-0854219c43aa', 'F9WC-3-2', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 00:36:12', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ff01deb8-9ef6-42d8-977f-9f79721735f1', 'F9WC-2', '', '2', 'REVOKE', 'TRAY', 'CARRY', '2021-08-17 17:09:13', '42', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ff83ca33-4188-48e0-8082-9a3e137f3288', 'F9WC-11-2', '', '10', 'OVER', 'TRAY', 'CARRY', '2021-08-17 18:24:21', '43', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ff9e839f-2402-4922-9430-cc317a3d5a98', 'F9WC-3-1', '', '1', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 23:40:06', '41', '');
INSERT INTO `kh_order_info_copy1` VALUES ('ffb7735b-7841-484d-a0be-a0a2ffd6952f', 'F9WC-1-2', '', '1', 'REVOKE', 'GOODS', 'CARRY', '2021-08-16 08:43:02', '-1', 'PAL21081607446');
INSERT INTO `kh_order_info_copy1` VALUES ('ffdccc9a-9580-4d7f-8400-c0395d0cd873', 'F9WC-4', '', '10', 'REVOKE', 'TRAY', 'CARRY', '2021-08-18 13:05:53', '41', '');

-- ----------------------------
-- Table structure for kh_order_info_static
-- ----------------------------
DROP TABLE IF EXISTS `kh_order_info_static`;
CREATE TABLE `kh_order_info_static` (
  `ORDER_ID` int(11) NOT NULL AUTO_INCREMENT,
  `START` varchar(255) NOT NULL,
  `TARGET` varchar(255) NOT NULL,
  `PRIORITY` int(11) NOT NULL DEFAULT '1',
  `STATUS` varchar(255) NOT NULL DEFAULT 'NEW',
  `MODE` varchar(255) NOT NULL DEFAULT 'IN',
  `TYPE` varchar(255) NOT NULL DEFAULT 'TYPE',
  `ENTERDATE` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`ORDER_ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='预定义的工单列表，用于在pad上显示/发送工单\r\n发送的工单应填写至表kh_order_info';

-- ----------------------------
-- Records of kh_order_info_static
-- ----------------------------

-- ----------------------------
-- Table structure for kh_parking_charging_info
-- ----------------------------
DROP TABLE IF EXISTS `kh_parking_charging_info`;
CREATE TABLE `kh_parking_charging_info` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `AGV_ID` int(11) DEFAULT NULL,
  `START` varchar(255) DEFAULT NULL,
  `TARGET` varchar(255) DEFAULT NULL,
  `STATUS` varchar(255) DEFAULT NULL,
  `TYPE` varchar(255) DEFAULT NULL,
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `FINISHDATE` varchar(255) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=685 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_parking_charging_info
-- ----------------------------
INSERT INTO `kh_parking_charging_info` VALUES ('344', '61', 'A10', 'P1', 'DONE', 'PARKING', '2021-06-15 17:32:55', '2021/6/20 15:2:3');
INSERT INTO `kh_parking_charging_info` VALUES ('345', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-15 17:33:53', '2021/6/20 15:2:16');
INSERT INTO `kh_parking_charging_info` VALUES ('346', '61', 'A10', 'P1', 'DONE', 'PARKING', '2021-06-15 17:40:20', '2021/6/15 17:41:18');
INSERT INTO `kh_parking_charging_info` VALUES ('347', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-15 17:41:18', '2021/6/15 17:41:48');
INSERT INTO `kh_parking_charging_info` VALUES ('348', '61', 'A10', 'P1', 'DONE', 'PARKING', '2021-06-20 14:29:02', '2021/6/20 14:30:0');
INSERT INTO `kh_parking_charging_info` VALUES ('349', '61', 'A10', 'P1', 'DONE', 'PARKING', '2021-06-20 14:36:41', '2021/6/20 14:37:39');
INSERT INTO `kh_parking_charging_info` VALUES ('350', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-20 14:37:39', '2021/6/20 14:37:44');
INSERT INTO `kh_parking_charging_info` VALUES ('351', '61', 'F9WC-1-1-P-W', 'P1', 'DONE', 'PARKING', '2021-06-20 14:42:27', '2021/6/20 15:2:3');
INSERT INTO `kh_parking_charging_info` VALUES ('352', '61', 'F9WC-1-1-P-W', 'P2', 'DONE', 'PARKING', '2021-06-20 15:00:50', '2021/6/20 15:2:3');
INSERT INTO `kh_parking_charging_info` VALUES ('353', '61', 'F9WC-1-1-P-W', 'P1', 'DONE', 'PARKING', '2021-06-20 15:01:01', '2021/6/20 15:2:3');
INSERT INTO `kh_parking_charging_info` VALUES ('354', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-20 15:02:03', '2021/6/20 15:2:16');
INSERT INTO `kh_parking_charging_info` VALUES ('355', '61', 'F9WC-1-1-P-W', 'P1', 'DONE', 'PARKING', '2021-06-20 15:06:58', '2021/6/20 15:8:1');
INSERT INTO `kh_parking_charging_info` VALUES ('356', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-20 15:08:01', '2021/6/20 15:8:56');
INSERT INTO `kh_parking_charging_info` VALUES ('357', '61', 'F9WC-1-2-P-W', 'P1', 'DONE', 'PARKING', '2021-06-20 15:10:18', '2021/6/20 15:11:24');
INSERT INTO `kh_parking_charging_info` VALUES ('358', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-20 15:11:24', '2021/6/20 15:11:56');
INSERT INTO `kh_parking_charging_info` VALUES ('359', '61', 'F9WC-2-P-W', 'P1', 'DONE', 'PARKING', '2021-06-20 15:21:55', '2021/6/20 15:22:46');
INSERT INTO `kh_parking_charging_info` VALUES ('360', '61', 'P1', 'P1', 'DONE', 'CHARGING', '2021-06-20 15:22:46', '2021/6/20 15:23:8');
INSERT INTO `kh_parking_charging_info` VALUES ('361', '61', 'A10', 'P1', 'DONE', 'PARKING', '2021-06-21 15:57:55', '2021/6/21 15:58:54');
INSERT INTO `kh_parking_charging_info` VALUES ('362', '61', 'P1', '', null, 'CHARGING', '2021-06-22 15:08:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('363', '61', 'A12', 'P1', null, 'PARKING', '2021-06-22 16:45:26', '');
INSERT INTO `kh_parking_charging_info` VALUES ('364', '61', 'A13', 'P1', null, 'PARKING', '2021-06-22 16:51:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('365', '61', 'P1', 'P1', null, 'CHARGING', '2021-06-22 16:52:25', '');
INSERT INTO `kh_parking_charging_info` VALUES ('366', '61', 'A14', 'P1', null, 'PARKING', '2021-06-22 17:40:05', '');
INSERT INTO `kh_parking_charging_info` VALUES ('367', '61', 'P1', 'P1', null, 'CHARGING', '2021-06-22 17:41:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('368', '61', 'A15', 'P1', null, 'PARKING', '2021-06-22 18:22:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('369', '61', 'A16', 'P1', null, 'PARKING', '2021-06-22 18:27:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('370', '61', 'P1', 'P1', null, 'CHARGING', '2021-06-22 18:28:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('371', '61', 'A17', 'P1', null, 'PARKING', '2021-06-22 18:31:27', '');
INSERT INTO `kh_parking_charging_info` VALUES ('372', '61', 'P1', 'P1', null, 'CHARGING', '2021-06-22 18:32:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('373', '61', 'A18', 'P1', null, 'PARKING', '2021-06-23 10:40:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('374', '61', 'P1', '', null, 'CHARGING', '2021-06-23 10:44:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('375', '61', 'A10', 'P1', null, 'PARKING', '2021-06-23 21:41:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('376', '61', 'A11', 'P1', null, 'PARKING', '2021-06-23 21:51:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('377', '61', 'P1', 'P1', null, 'CHARGING', '2021-06-23 21:52:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('378', '61', 'A12', 'P1', null, 'PARKING', '2021-06-23 22:00:06', '');
INSERT INTO `kh_parking_charging_info` VALUES ('379', '61', 'A12', 'P1', null, 'PARKING', '2021-06-23 23:05:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('380', '61', 'P1', 'P1', null, 'CHARGING', '2021-06-23 23:06:25', '');
INSERT INTO `kh_parking_charging_info` VALUES ('381', '1', 'P1', '', null, 'CHARGING', '2021-06-25 16:02:42', '');
INSERT INTO `kh_parking_charging_info` VALUES ('382', '1', 'P1', '', null, 'CHARGING', '2021-06-25 16:29:36', '');
INSERT INTO `kh_parking_charging_info` VALUES ('383', '1', 'P1', '', null, 'CHARGING', '2021-06-25 16:31:43', '');
INSERT INTO `kh_parking_charging_info` VALUES ('384', '1', 'P1', '', null, 'CHARGING', '2021-06-25 17:07:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('385', '61', 'A12', 'P1', null, 'PARKING', '2021-06-27 11:37:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('386', '61', 'A12', 'P2', null, 'PARKING', '2021-06-27 11:38:54', '');
INSERT INTO `kh_parking_charging_info` VALUES ('387', '61', 'A11', 'P3', null, 'PARKING', '2021-06-27 11:39:06', '');
INSERT INTO `kh_parking_charging_info` VALUES ('388', '61', 'A11', 'P1', null, 'PARKING', '2021-06-27 11:39:22', '');
INSERT INTO `kh_parking_charging_info` VALUES ('389', '51', 'P1', '', null, 'CHARGING', '2021-07-13 13:33:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('390', '61', 'A9', 'P2', null, 'PARKING', '2021-07-16 11:18:09', '');
INSERT INTO `kh_parking_charging_info` VALUES ('391', '61', 'A9', 'P1', null, 'PARKING', '2021-07-16 11:21:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('392', '61', 'None', 'P1', null, 'PARKING', '2021-07-16 11:23:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('393', '61', 'F9WC-1-1-G-W', 'P1', null, 'PARKING', '2021-07-17 22:12:42', '');
INSERT INTO `kh_parking_charging_info` VALUES ('394', '61', 'F9WC-1-1-G-W', 'P2', null, 'PARKING', '2021-07-17 22:14:12', '');
INSERT INTO `kh_parking_charging_info` VALUES ('395', '61', 'F9WC-1-1-G-W', 'P1', null, 'PARKING', '2021-07-17 22:26:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('396', '61', 'F9WC-1-1-G-W', 'P1', null, 'PARKING', '2021-07-17 22:48:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('397', '61', 'None', 'P1', null, 'PARKING', '2021-07-17 22:53:35', '');
INSERT INTO `kh_parking_charging_info` VALUES ('398', '61', 'P1', '', null, 'CHARGING', '2021-07-17 22:56:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('399', '61', 'A7', 'P1', null, 'PARKING', '2021-07-17 23:04:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('400', '61', 'P1', 'P1', null, 'CHARGING', '2021-07-17 23:05:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('401', '61', 'A7', 'P1', null, 'PARKING', '2021-07-17 23:21:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('402', '61', 'P1', 'P1', null, 'CHARGING', '2021-07-17 23:22:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('403', '61', 'A7', 'P1', null, 'PARKING', '2021-07-17 23:40:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('404', '61', 'P1', 'P1', null, 'CHARGING', '2021-07-17 23:41:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('405', '61', 'A7', 'P1', null, 'PARKING', '2021-07-26 17:51:16', '');
INSERT INTO `kh_parking_charging_info` VALUES ('406', '61', 'A7', 'P1', null, 'PARKING', '2021-07-27 14:32:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('407', '61', 'P1', 'P1', null, 'CHARGING', '2021-07-27 14:32:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('408', '61', 'A7', 'P1', null, 'PARKING', '2021-07-27 14:46:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('409', '61', 'P1', 'P1', null, 'CHARGING', '2021-07-27 14:47:06', '');
INSERT INTO `kh_parking_charging_info` VALUES ('410', '61', 'A7', 'P1', null, 'PARKING', '2021-07-27 15:18:47', '');
INSERT INTO `kh_parking_charging_info` VALUES ('411', '61', 'P1', 'P1', null, 'CHARGING', '2021-07-27 15:19:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('412', '61', 'P1', '', null, 'CHARGING', '2021-08-04 18:20:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('413', '61', 'A-CONFIRM', 'P1', null, 'PARKING', '2021-08-04 18:29:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('414', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-04 18:30:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('415', '61', 'P1', '', null, 'CHARGING', '2021-08-05 10:42:44', '');
INSERT INTO `kh_parking_charging_info` VALUES ('416', '61', 'F9WC-1-2-G-W', 'P1', null, 'PARKING', '2021-08-05 10:50:48', '');
INSERT INTO `kh_parking_charging_info` VALUES ('417', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-05 10:51:45', '');
INSERT INTO `kh_parking_charging_info` VALUES ('418', '61', 'P1', '', null, 'CHARGING', '2021-08-05 16:05:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('419', '61', 'P1', '', null, 'CHARGING', '2021-08-05 16:12:29', '');
INSERT INTO `kh_parking_charging_info` VALUES ('420', '61', 'A-CONFIRM', 'P1', null, 'PARKING', '2021-08-05 16:20:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('421', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-05 16:21:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('422', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-05 16:35:29', '');
INSERT INTO `kh_parking_charging_info` VALUES ('423', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-05 16:36:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('424', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-05 17:02:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('425', '61', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-05 17:04:06', '');
INSERT INTO `kh_parking_charging_info` VALUES ('426', '61', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-05 17:06:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('427', '62', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-05 17:06:52', '');
INSERT INTO `kh_parking_charging_info` VALUES ('428', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-05 17:08:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('429', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-06 10:30:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('430', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-06 10:31:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('431', '63', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-06 10:32:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('432', '61', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-06 10:34:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('433', '63', 'P2', 'P2', null, 'CHARGING', '2021-08-06 10:34:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('434', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-06 11:02:03', '');
INSERT INTO `kh_parking_charging_info` VALUES ('435', '62', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-06 11:03:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('436', '61', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-06 11:16:53', '');
INSERT INTO `kh_parking_charging_info` VALUES ('437', '61', 'P1', '', null, 'CHARGING', '2021-08-06 11:20:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('438', '62', 'P2', '', null, 'CHARGING', '2021-08-06 11:20:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('439', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-06 11:22:39', '');
INSERT INTO `kh_parking_charging_info` VALUES ('440', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-06 11:23:11', '');
INSERT INTO `kh_parking_charging_info` VALUES ('441', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-06 11:24:25', '');
INSERT INTO `kh_parking_charging_info` VALUES ('442', '61', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-06 11:26:13', '');
INSERT INTO `kh_parking_charging_info` VALUES ('443', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-06 11:26:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('444', '61', 'P3', 'P2', null, 'PARKING', '2021-08-06 11:28:45', '');
INSERT INTO `kh_parking_charging_info` VALUES ('445', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-06 11:31:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('446', '62', 'P2', '', null, 'CHARGING', '2021-08-06 11:51:08', '');
INSERT INTO `kh_parking_charging_info` VALUES ('447', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-06 13:48:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('448', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-06 13:51:02', '');
INSERT INTO `kh_parking_charging_info` VALUES ('449', '62', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-06 14:25:42', '');
INSERT INTO `kh_parking_charging_info` VALUES ('450', '63', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-06 14:34:54', '');
INSERT INTO `kh_parking_charging_info` VALUES ('451', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-06 16:49:00', '');
INSERT INTO `kh_parking_charging_info` VALUES ('452', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-06 16:51:03', '');
INSERT INTO `kh_parking_charging_info` VALUES ('453', '62', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-06 17:07:33', '');
INSERT INTO `kh_parking_charging_info` VALUES ('454', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-06 17:39:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('455', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-06 17:42:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('456', '62', 'A1', 'P2', null, 'PARKING', '2021-08-06 18:22:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('457', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-06 18:27:39', '');
INSERT INTO `kh_parking_charging_info` VALUES ('458', '63', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-06 18:29:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('459', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-06 18:29:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('460', '61', 'A-CONFIRM', 'P1', null, 'PARKING', '2021-08-09 13:38:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('461', '62', 'F9WC-1-2-G-W', 'P2', null, 'PARKING', '2021-08-09 13:38:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('462', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-09 14:08:55', '');
INSERT INTO `kh_parking_charging_info` VALUES ('463', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-09 14:09:27', '');
INSERT INTO `kh_parking_charging_info` VALUES ('464', '61', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-09 14:10:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('465', '63', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-09 14:12:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('466', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-09 14:12:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('467', '63', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-09 14:13:00', '');
INSERT INTO `kh_parking_charging_info` VALUES ('468', '63', 'None', 'P3', null, 'PARKING', '2021-08-09 14:14:13', '');
INSERT INTO `kh_parking_charging_info` VALUES ('469', '63', 'None', 'P3', null, 'PARKING', '2021-08-09 14:14:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('470', '63', 'None', 'P4', null, 'PARKING', '2021-08-09 14:14:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('471', '63', 'None', 'P3', null, 'PARKING', '2021-08-09 14:16:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('472', '63', 'None', 'P3', null, 'PARKING', '2021-08-09 14:16:39', '');
INSERT INTO `kh_parking_charging_info` VALUES ('473', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-09 15:29:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('474', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-09 15:29:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('475', '63', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-09 15:30:39', '');
INSERT INTO `kh_parking_charging_info` VALUES ('476', '62', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-09 15:35:44', '');
INSERT INTO `kh_parking_charging_info` VALUES ('477', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-11 10:31:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('478', '63', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-11 10:33:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('479', '62', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-11 10:35:02', '');
INSERT INTO `kh_parking_charging_info` VALUES ('480', '62', 'P2', 'P4', null, 'CHARGING', '2021-08-11 11:20:04', '');
INSERT INTO `kh_parking_charging_info` VALUES ('481', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-11 11:23:48', '');
INSERT INTO `kh_parking_charging_info` VALUES ('482', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-11 11:24:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('483', '63', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-11 11:25:36', '');
INSERT INTO `kh_parking_charging_info` VALUES ('484', '62', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-11 11:27:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('485', '63', 'P2', 'P2', null, 'CHARGING', '2021-08-11 11:27:38', '');
INSERT INTO `kh_parking_charging_info` VALUES ('486', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-11 12:01:26', '');
INSERT INTO `kh_parking_charging_info` VALUES ('487', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-11 12:01:57', '');
INSERT INTO `kh_parking_charging_info` VALUES ('488', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-11 12:03:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('489', '63', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-11 12:05:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('490', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-11 12:05:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('491', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-12 10:45:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('492', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-12 10:45:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('493', '62', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-12 10:46:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('494', '62', 'P3', 'P2', null, 'PARKING', '2021-08-12 11:30:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('495', '62', 'P2', '', null, 'CHARGING', '2021-08-12 11:32:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('496', '61', 'None', 'P1', null, 'PARKING', '2021-08-12 14:06:13', '');
INSERT INTO `kh_parking_charging_info` VALUES ('497', '61', 'P1', '', null, 'CHARGING', '2021-08-12 15:09:53', '');
INSERT INTO `kh_parking_charging_info` VALUES ('498', '62', 'P2', '', null, 'CHARGING', '2021-08-12 15:09:53', '');
INSERT INTO `kh_parking_charging_info` VALUES ('499', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-12 15:26:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('500', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-12 15:26:54', '');
INSERT INTO `kh_parking_charging_info` VALUES ('501', '61', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-12 15:34:16', '');
INSERT INTO `kh_parking_charging_info` VALUES ('502', '61', 'P3', 'P2', null, 'PARKING', '2021-08-12 15:58:15', '');
INSERT INTO `kh_parking_charging_info` VALUES ('503', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-12 16:00:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('504', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-12 16:11:04', '');
INSERT INTO `kh_parking_charging_info` VALUES ('505', '62', 'A-RELEASE', 'P3', null, 'PARKING', '2021-08-12 16:15:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('506', '61', 'A-RELEASE', 'P4', null, 'PARKING', '2021-08-12 16:16:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('507', '61', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-12 16:17:22', '');
INSERT INTO `kh_parking_charging_info` VALUES ('508', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-12 16:19:35', '');
INSERT INTO `kh_parking_charging_info` VALUES ('509', '62', 'P3', 'P1', null, 'PARKING', '2021-08-12 16:34:21', '');
INSERT INTO `kh_parking_charging_info` VALUES ('510', '61', 'A-CONFIRM', 'P1', null, 'PARKING', '2021-08-12 17:20:03', '');
INSERT INTO `kh_parking_charging_info` VALUES ('511', '63', 'A-CONFIRM', 'P2', null, 'PARKING', '2021-08-12 17:20:22', '');
INSERT INTO `kh_parking_charging_info` VALUES ('512', '63', 'P2', 'P2', null, 'CHARGING', '2021-08-12 17:20:36', '');
INSERT INTO `kh_parking_charging_info` VALUES ('513', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-12 17:20:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('514', '62', 'P1', '', null, 'CHARGING', '2021-08-12 17:21:11', '');
INSERT INTO `kh_parking_charging_info` VALUES ('515', '61', 'P1', '', null, 'CHARGING', '2021-08-12 17:57:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('516', '62', 'P2', '', null, 'CHARGING', '2021-08-12 17:57:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('517', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-12 18:32:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('518', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-12 18:32:52', '');
INSERT INTO `kh_parking_charging_info` VALUES ('519', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-13 17:31:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('520', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-13 17:31:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('521', '62', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-13 17:47:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('522', '62', 'P2', 'P2', null, 'CHARGING', '2021-08-13 17:50:00', '');
INSERT INTO `kh_parking_charging_info` VALUES ('523', '62', 'None', 'P2', null, 'PARKING', '2021-08-13 17:56:26', '');
INSERT INTO `kh_parking_charging_info` VALUES ('524', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-14 16:44:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('525', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-14 16:44:52', '');
INSERT INTO `kh_parking_charging_info` VALUES ('526', '61', 'A9', 'P1', null, 'PARKING', '2021-08-14 16:51:56', '');
INSERT INTO `kh_parking_charging_info` VALUES ('527', '61', 'P1', '', null, 'CHARGING', '2021-08-14 17:25:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('528', '61', 'P1', '', null, 'CHARGING', '2021-08-14 17:36:11', '');
INSERT INTO `kh_parking_charging_info` VALUES ('529', '61', 'P1', '', null, 'CHARGING', '2021-08-14 17:48:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('530', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-14 17:59:03', '');
INSERT INTO `kh_parking_charging_info` VALUES ('531', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-14 17:59:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('532', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-14 18:52:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('533', '61', 'F9WC-5-1-P-W', 'P1', null, 'PARKING', '2021-08-14 18:57:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('534', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-14 18:59:55', '');
INSERT INTO `kh_parking_charging_info` VALUES ('535', '61', 'X-CONFIRM', 'P1', null, 'PARKING', '2021-08-15 14:46:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('536', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-15 14:49:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('537', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-15 14:53:59', '');
INSERT INTO `kh_parking_charging_info` VALUES ('538', '61', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-15 15:01:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('539', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-15 15:03:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('540', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-17 15:47:55', '');
INSERT INTO `kh_parking_charging_info` VALUES ('541', '61', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-17 16:02:38', '');
INSERT INTO `kh_parking_charging_info` VALUES ('542', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-17 16:05:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('543', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 09:17:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('544', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 09:32:21', '');
INSERT INTO `kh_parking_charging_info` VALUES ('545', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 09:58:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('546', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-18 09:58:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('547', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 11:41:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('548', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-18 11:41:47', '');
INSERT INTO `kh_parking_charging_info` VALUES ('549', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 11:45:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('550', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-18 11:46:11', '');
INSERT INTO `kh_parking_charging_info` VALUES ('551', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 11:49:42', '');
INSERT INTO `kh_parking_charging_info` VALUES ('552', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-18 11:50:03', '');
INSERT INTO `kh_parking_charging_info` VALUES ('553', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 11:52:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('554', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-18 11:52:54', '');
INSERT INTO `kh_parking_charging_info` VALUES ('555', '63', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 11:56:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('556', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-18 11:56:40', '');
INSERT INTO `kh_parking_charging_info` VALUES ('557', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 11:59:16', '');
INSERT INTO `kh_parking_charging_info` VALUES ('558', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-18 11:59:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('559', '61', 'F9WC-5-1-P-W', 'P1', null, 'PARKING', '2021-08-18 12:03:16', '');
INSERT INTO `kh_parking_charging_info` VALUES ('560', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-18 13:30:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('561', '63', 'A-RELEASE', 'P2', null, 'PARKING', '2021-08-18 13:30:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('562', '62', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-18 13:32:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('563', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-18 13:33:11', '');
INSERT INTO `kh_parking_charging_info` VALUES ('564', '63', 'P2', 'P2', null, 'CHARGING', '2021-08-18 13:33:37', '');
INSERT INTO `kh_parking_charging_info` VALUES ('565', '61', 'A1', 'P1', null, 'PARKING', '2021-08-19 16:12:53', '');
INSERT INTO `kh_parking_charging_info` VALUES ('566', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 16:13:43', '');
INSERT INTO `kh_parking_charging_info` VALUES ('567', '61', 'A1', 'P1', null, 'PARKING', '2021-08-19 16:55:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('568', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 16:55:53', '');
INSERT INTO `kh_parking_charging_info` VALUES ('569', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-19 17:08:54', '');
INSERT INTO `kh_parking_charging_info` VALUES ('570', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 17:09:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('571', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-19 17:16:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('572', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 17:16:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('573', '61', 'A-RELEASE', 'P1', null, 'PARKING', '2021-08-19 17:29:43', '');
INSERT INTO `kh_parking_charging_info` VALUES ('574', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 17:30:04', '');
INSERT INTO `kh_parking_charging_info` VALUES ('575', '61', 'F9WC-1-1-P-W', 'P1', null, 'PARKING', '2021-08-19 17:43:23', '');
INSERT INTO `kh_parking_charging_info` VALUES ('576', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 17:45:58', '');
INSERT INTO `kh_parking_charging_info` VALUES ('577', '61', 'F9WC-1-1-P-W', 'P1', null, 'PARKING', '2021-08-19 17:54:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('578', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 17:56:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('579', '61', 'F9WC-3-1-G-W', 'P1', null, 'PARKING', '2021-08-19 18:12:55', '');
INSERT INTO `kh_parking_charging_info` VALUES ('580', '61', 'F9WC-3-1-G-W', 'P1', null, 'PARKING', '2021-08-19 18:13:26', '');
INSERT INTO `kh_parking_charging_info` VALUES ('581', '61', 'F9WC-3-1-G-W', 'P1', null, 'PARKING', '2021-08-19 18:18:12', '');
INSERT INTO `kh_parking_charging_info` VALUES ('582', '61', 'B2', 'P2', null, 'PARKING', '2021-08-19 18:20:44', '');
INSERT INTO `kh_parking_charging_info` VALUES ('583', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-19 18:23:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('584', '61', 'B3', 'P2', null, 'PARKING', '2021-08-19 18:24:55', '');
INSERT INTO `kh_parking_charging_info` VALUES ('585', '61', 'A1', 'P1', null, 'PARKING', '2021-08-19 18:51:16', '');
INSERT INTO `kh_parking_charging_info` VALUES ('586', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 18:52:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('587', '63', 'A1', 'P1', null, 'PARKING', '2021-08-19 18:56:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('588', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-19 18:57:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('589', '61', 'P1', '', null, 'CHARGING', '2021-08-19 19:01:04', '');
INSERT INTO `kh_parking_charging_info` VALUES ('590', '62', 'P2', '', null, 'CHARGING', '2021-08-19 19:01:04', '');
INSERT INTO `kh_parking_charging_info` VALUES ('591', '62', 'A1', 'P1', null, 'PARKING', '2021-08-19 19:12:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('592', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-19 19:13:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('593', '61', 'A1', 'P1', null, 'PARKING', '2021-08-19 19:16:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('594', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-19 19:17:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('595', '63', 'A1', 'P2', null, 'PARKING', '2021-08-19 19:18:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('596', '63', 'P2', 'P2', null, 'CHARGING', '2021-08-19 19:22:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('597', '62', 'A1', 'P1', null, 'PARKING', '2021-08-20 15:26:19', '');
INSERT INTO `kh_parking_charging_info` VALUES ('598', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-20 15:27:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('599', '61', 'A1', 'P2', null, 'PARKING', '2021-08-20 15:27:43', '');
INSERT INTO `kh_parking_charging_info` VALUES ('600', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-20 15:31:29', '');
INSERT INTO `kh_parking_charging_info` VALUES ('601', '63', 'F9WC-12-1-G-W', 'P1', null, 'PARKING', '2021-08-20 15:31:44', '');
INSERT INTO `kh_parking_charging_info` VALUES ('602', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-20 15:32:26', '');
INSERT INTO `kh_parking_charging_info` VALUES ('603', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-20 15:35:26', '');
INSERT INTO `kh_parking_charging_info` VALUES ('604', '62', 'A1', 'P1', null, 'PARKING', '2021-08-20 15:36:53', '');
INSERT INTO `kh_parking_charging_info` VALUES ('605', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-20 15:38:12', '');
INSERT INTO `kh_parking_charging_info` VALUES ('606', '63', 'A1', 'P1', null, 'PARKING', '2021-08-20 15:47:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('607', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-20 15:49:09', '');
INSERT INTO `kh_parking_charging_info` VALUES ('608', '61', 'A1', 'P1', null, 'PARKING', '2021-08-20 15:52:02', '');
INSERT INTO `kh_parking_charging_info` VALUES ('609', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-20 15:53:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('610', '63', 'A1', 'P1', null, 'PARKING', '2021-08-20 15:58:57', '');
INSERT INTO `kh_parking_charging_info` VALUES ('611', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-20 16:00:20', '');
INSERT INTO `kh_parking_charging_info` VALUES ('612', '62', 'A1', 'P1', null, 'PARKING', '2021-08-20 16:03:41', '');
INSERT INTO `kh_parking_charging_info` VALUES ('613', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-20 16:05:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('614', '61', 'A1', 'P1', null, 'PARKING', '2021-08-20 16:13:00', '');
INSERT INTO `kh_parking_charging_info` VALUES ('615', '61', 'P1', 'P1', null, 'CHARGING', '2021-08-20 16:14:03', '');
INSERT INTO `kh_parking_charging_info` VALUES ('616', '63', 'A1', 'P1', null, 'PARKING', '2021-08-20 16:15:12', '');
INSERT INTO `kh_parking_charging_info` VALUES ('617', '62', 'A1', 'P2', null, 'PARKING', '2021-08-20 16:17:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('618', '62', 'A1', 'P1', null, 'PARKING', '2021-08-20 18:26:55', '');
INSERT INTO `kh_parking_charging_info` VALUES ('619', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-20 18:28:05', '');
INSERT INTO `kh_parking_charging_info` VALUES ('620', '63', 'A1', 'P1', null, 'PARKING', '2021-08-20 18:30:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('621', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-20 18:31:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('622', '62', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-20 19:32:04', '');
INSERT INTO `kh_parking_charging_info` VALUES ('623', '61', 'A1', 'P2', null, 'PARKING', '2021-08-20 19:33:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('624', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-20 19:34:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('625', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-20 19:36:00', '');
INSERT INTO `kh_parking_charging_info` VALUES ('626', '61', 'B6', 'P2', null, 'PARKING', '2021-08-21 09:01:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('627', '61', 'B8', 'P1', null, 'PARKING', '2021-08-21 09:03:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('628', '62', 'B2', 'P2', null, 'PARKING', '2021-08-21 09:06:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('629', '62', 'P2', '', null, 'CHARGING', '2021-08-22 15:28:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('630', '61', 'P1', '', null, 'CHARGING', '2021-08-22 15:34:40', '');
INSERT INTO `kh_parking_charging_info` VALUES ('631', '62', 'P2', '', null, 'CHARGING', '2021-08-22 15:34:40', '');
INSERT INTO `kh_parking_charging_info` VALUES ('632', '61', 'P1', '', null, 'CHARGING', '2021-08-22 15:52:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('633', '62', 'P2', '', null, 'CHARGING', '2021-08-22 15:52:18', '');
INSERT INTO `kh_parking_charging_info` VALUES ('634', '61', 'P1', '', null, 'CHARGING', '2021-08-23 13:54:45', '');
INSERT INTO `kh_parking_charging_info` VALUES ('635', '62', 'P2', '', null, 'CHARGING', '2021-08-23 13:54:45', '');
INSERT INTO `kh_parking_charging_info` VALUES ('636', '61', 'P1', '', null, 'CHARGING', '2021-08-23 14:49:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('637', '62', 'P2', '', null, 'CHARGING', '2021-08-23 14:49:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('638', '62', 'P2', '', null, 'CHARGING', '2021-08-23 15:12:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('639', '61', 'P1', '', null, 'CHARGING', '2021-08-23 15:12:34', '');
INSERT INTO `kh_parking_charging_info` VALUES ('640', '62', 'P2', '', null, 'CHARGING', '2021-08-23 15:29:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('641', '64', 'P4', '', null, 'CHARGING', '2021-08-23 15:29:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('642', '63', 'P3', 'P1', null, 'PARKING', '2021-08-23 15:29:52', '');
INSERT INTO `kh_parking_charging_info` VALUES ('643', '61', 'P1', '', null, 'CHARGING', '2021-08-23 15:30:43', '');
INSERT INTO `kh_parking_charging_info` VALUES ('644', '62', 'P2', '', null, 'CHARGING', '2021-08-23 15:30:43', '');
INSERT INTO `kh_parking_charging_info` VALUES ('645', '63', 'P3', 'P1', null, 'PARKING', '2021-08-23 15:30:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('646', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-23 15:32:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('647', '62', 'A1', 'P1', null, 'PARKING', '2021-08-23 15:33:07', '');
INSERT INTO `kh_parking_charging_info` VALUES ('648', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-23 15:34:10', '');
INSERT INTO `kh_parking_charging_info` VALUES ('649', '64', 'A1', 'P1', null, 'PARKING', '2021-08-23 15:34:58', '');
INSERT INTO `kh_parking_charging_info` VALUES ('650', '61', 'A1', 'P2', null, 'PARKING', '2021-08-23 15:41:24', '');
INSERT INTO `kh_parking_charging_info` VALUES ('651', '62', 'A1', 'P3', null, 'PARKING', '2021-08-23 15:51:48', '');
INSERT INTO `kh_parking_charging_info` VALUES ('652', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 10:56:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('653', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 10:56:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('654', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 10:56:48', '');
INSERT INTO `kh_parking_charging_info` VALUES ('655', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 10:59:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('656', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 10:59:49', '');
INSERT INTO `kh_parking_charging_info` VALUES ('657', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 10:59:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('658', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 11:18:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('659', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 11:18:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('660', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 11:18:32', '');
INSERT INTO `kh_parking_charging_info` VALUES ('661', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 11:24:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('662', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 11:24:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('663', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 11:24:02', '');
INSERT INTO `kh_parking_charging_info` VALUES ('664', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 11:27:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('665', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 11:27:46', '');
INSERT INTO `kh_parking_charging_info` VALUES ('666', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 11:27:47', '');
INSERT INTO `kh_parking_charging_info` VALUES ('667', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 11:38:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('668', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 11:38:50', '');
INSERT INTO `kh_parking_charging_info` VALUES ('669', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 11:38:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('670', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 11:40:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('671', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 11:40:30', '');
INSERT INTO `kh_parking_charging_info` VALUES ('672', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 11:40:31', '');
INSERT INTO `kh_parking_charging_info` VALUES ('673', '63', 'X-RELEASE', 'P1', null, 'PARKING', '2021-08-24 11:44:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('674', '62', 'P3', 'P2', null, 'PARKING', '2021-08-24 11:44:28', '');
INSERT INTO `kh_parking_charging_info` VALUES ('675', '61', 'None', 'P3', null, 'PARKING', '2021-08-24 11:44:29', '');
INSERT INTO `kh_parking_charging_info` VALUES ('676', '62', 'P2', '', null, 'CHARGING', '2021-08-26 11:15:14', '');
INSERT INTO `kh_parking_charging_info` VALUES ('677', '62', 'A1', 'P1', null, 'PARKING', '2021-08-26 11:40:57', '');
INSERT INTO `kh_parking_charging_info` VALUES ('678', '61', 'F9WC-1-1-P-W', 'P2', null, 'PARKING', '2021-08-26 11:41:33', '');
INSERT INTO `kh_parking_charging_info` VALUES ('679', '62', 'P1', 'P1', null, 'CHARGING', '2021-08-26 11:42:05', '');
INSERT INTO `kh_parking_charging_info` VALUES ('680', '61', 'P2', 'P2', null, 'CHARGING', '2021-08-26 11:45:17', '');
INSERT INTO `kh_parking_charging_info` VALUES ('681', '63', 'A1', 'P1', null, 'PARKING', '2021-08-26 11:45:54', '');
INSERT INTO `kh_parking_charging_info` VALUES ('682', '63', 'P1', 'P1', null, 'CHARGING', '2021-08-26 11:47:01', '');
INSERT INTO `kh_parking_charging_info` VALUES ('683', '65', 'None', 'P1', null, 'PARKING', '2021-08-31 15:50:51', '');
INSERT INTO `kh_parking_charging_info` VALUES ('684', '61', 'None', 'P5', null, 'PARKING', '2021-08-31 15:50:51', '');

-- ----------------------------
-- Table structure for kh_plc_data
-- ----------------------------
DROP TABLE IF EXISTS `kh_plc_data`;
CREATE TABLE `kh_plc_data` (
  `DEV_ID` varchar(11) NOT NULL COMMENT '设备PLC标识号',
  `DEV_NAME` varchar(255) DEFAULT NULL COMMENT '设备名',
  `DEV_TYPE` varchar(255) DEFAULT NULL COMMENT '设备类型(SHORT或者BOOL，指代PLC地址类型)',
  `PLC_IP` varchar(255) DEFAULT '192.168.1.80' COMMENT 'PLC-IP',
  `PLC_REMOTE_NODE` varchar(11) DEFAULT '80' COMMENT 'PLC远程端口（默认80）',
  `PLC_PORT` varchar(11) DEFAULT '9600' COMMENT 'PLC以太网端口号（FINS协议默认使用的以太网端口为9600）',
  `PLC_VIRTUAL_PORT` varchar(255) DEFAULT NULL COMMENT 'PLC虚拟地址（类比为KEY）',
  `PLC_TRIGGER` varchar(255) DEFAULT NULL COMMENT 'PLC状态（类比为VALUE）',
  `MSG_STATUS` varchar(255) DEFAULT 'FALSE' COMMENT '该请求是否发送成功\r\nSENDING：需要发送消息\r\nIDLE：复位状态，不需要发送\r\nSEND：已发送',
  `READ_STATUS` varchar(255) DEFAULT NULL COMMENT '是否需要从PLC读取:\r\nREADING：读取一次\r\nREADED：读取完成\r\nIDLE：复位\r\nAUTO：持续读取',
  `READ_TIMES` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP COMMENT '读取成功次数',
  PRIMARY KEY (`DEV_ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_plc_data
-- ----------------------------
INSERT INTO `kh_plc_data` VALUES ('01', 'A1', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.00', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('02', 'A2', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.01', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('03', 'A3', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.02', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('04', 'A4', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.03', 'FALSE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('05', 'A5', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.04', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('06', 'A6', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.05', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('07', 'A7', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.06', 'FALSE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('08', 'A8', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.07', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:52');
INSERT INTO `kh_plc_data` VALUES ('09', 'A9', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.08', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('10', 'A10', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.09', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('11', 'A11', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.10', 'FALSE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('12', 'A12', 'BOOL', '192.168.1.80', '80', '9600', 'CIO0.11', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('13', 'B1', 'BOOL', '192.168.1.80', '80', '9600', 'CIO2.03', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('14', 'B2', 'BOOL', '192.168.1.80', '80', '9600', 'CIO2.02', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('15', 'B3', 'BOOL', '192.168.1.80', '80', '9600', 'CIO2.01', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('16', 'B4', 'BOOL', '192.168.1.80', '80', '9600', 'CIO2.00', 'FALSE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('17', 'B5', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.11', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('18', 'B6', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.10', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('19', 'B7', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.09', 'FALSE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('20', 'B8', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.08', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('21', 'B9', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.07', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('22', 'B10', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.06', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('23', 'B11', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.05', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('24', 'B12', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.04', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('25', 'B13', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.03', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('26', 'B14', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.02', 'FALSE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('27', 'B15', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.01', 'TRUE', 'IDLE', 'IDLE', '2021-08-14 16:22:53');
INSERT INTO `kh_plc_data` VALUES ('28', 'B16', 'BOOL', '192.168.1.80', '80', '9600', 'CIO1.00', 'FALSE', 'IDLE', 'IDLE', '2021-08-26 22:35:03');
INSERT INTO `kh_plc_data` VALUES ('29', 'C1', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.03', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:42');
INSERT INTO `kh_plc_data` VALUES ('30', 'C2', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.02', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:42');
INSERT INTO `kh_plc_data` VALUES ('31', 'C3', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.01', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:42');
INSERT INTO `kh_plc_data` VALUES ('32', 'C4', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.00', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:42');
INSERT INTO `kh_plc_data` VALUES ('33', 'C5', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.11', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:42');
INSERT INTO `kh_plc_data` VALUES ('34', 'C6', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.10', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('35', 'C7', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.09', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('36', 'C8', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.08', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('37', 'C9', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.07', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('38', 'C10', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.06', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('39', 'C11', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.05', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('40', 'C12', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.04', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('41', 'C13', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.03', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('42', 'C14', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.02', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('43', 'C15', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.01', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('44', 'C16', 'BOOL', '192.168.1.81', '80', '9600', 'CIO0.00', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('45', 'D1', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.11', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('46', 'D2', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.10', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('47', 'D3', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.09', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('48', 'D4', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.08', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('49', 'D5', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.07', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('50', 'D6', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.06', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('51', 'D7', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.05', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('52', 'D8', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.04', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('53', 'D9', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.03', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('54', 'D10', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.02', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('55', 'D11', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.01', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('56', 'D12', 'BOOL', '192.168.1.81', '80', '9600', 'CIO2.00', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('57', 'D13', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.11', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('58', 'D14', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.10', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('59', 'D15', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.09', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('60', 'D16', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.08', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('61', 'D17', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.07', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('62', 'D18', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.06', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('63', 'D19', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.05', 'FALSE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');
INSERT INTO `kh_plc_data` VALUES ('64', 'D20', 'BOOL', '192.168.1.81', '80', '9600', 'CIO1.04', 'TRUE', 'IDLE', 'IDLE', '2021-08-28 00:54:43');

-- ----------------------------
-- Table structure for kh_region_info
-- ----------------------------
DROP TABLE IF EXISTS `kh_region_info`;
CREATE TABLE `kh_region_info` (
  `ID` int(11) NOT NULL,
  `REGION` varchar(255) NOT NULL COMMENT '点阵',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_region_info
-- ----------------------------
INSERT INTO `kh_region_info` VALUES ('1', '(-2.31729,78.2318) (38.0963,78.2318) (78.5098,78.2318) (78.5098,83.0054) (78.5098,87.779) (38.0963,87.779) (-2.31729,87.779) (-2.31729,83.0054)');

-- ----------------------------
-- Table structure for kh_report_order_info
-- ----------------------------
DROP TABLE IF EXISTS `kh_report_order_info`;
CREATE TABLE `kh_report_order_info` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `ORDER_ID` varchar(255) DEFAULT NULL,
  `AGV_ID` int(11) DEFAULT NULL,
  `START` varchar(255) DEFAULT NULL,
  `TARGET` varchar(255) DEFAULT NULL,
  `PRIORITY` int(11) DEFAULT NULL,
  `STATUS` varchar(255) DEFAULT NULL,
  `MODE` varchar(255) DEFAULT NULL,
  `TYPE` varchar(255) DEFAULT NULL,
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `FINISHDATE` varchar(255) DEFAULT '',
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_report_order_info
-- ----------------------------

-- ----------------------------
-- Table structure for kh_report_rfid_info
-- ----------------------------
DROP TABLE IF EXISTS `kh_report_rfid_info`;
CREATE TABLE `kh_report_rfid_info` (
  `AGV_ID` int(11) NOT NULL,
  `RFID_INFO` varchar(255) DEFAULT NULL,
  `STATUS` varchar(255) DEFAULT NULL,
  `FLAG` varchar(255) DEFAULT NULL,
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`AGV_ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of kh_report_rfid_info
-- ----------------------------
INSERT INTO `kh_report_rfid_info` VALUES ('1', 'XD8S200411788', 'SUCCESS', 'NEW', '2021-08-10 21:04:44');

-- ----------------------------
-- Table structure for mode_manage
-- ----------------------------
DROP TABLE IF EXISTS `mode_manage`;
CREATE TABLE `mode_manage` (
  `ID` int(11) DEFAULT NULL,
  `TASK_NAME` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`TASK_NAME`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of mode_manage
-- ----------------------------
INSERT INTO `mode_manage` VALUES ('2', 'GOODS');
INSERT INTO `mode_manage` VALUES ('1', 'TRAY');

-- ----------------------------
-- Table structure for parking_manage
-- ----------------------------
DROP TABLE IF EXISTS `parking_manage`;
CREATE TABLE `parking_manage` (
  `ID` int(11) NOT NULL,
  `STATION_NAME` varchar(255) DEFAULT NULL,
  `IS_CHARGING` varchar(255) DEFAULT NULL,
  `STATUS` varchar(255) DEFAULT NULL,
  `AGV_TYPE` int(11) DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of parking_manage
-- ----------------------------
INSERT INTO `parking_manage` VALUES ('1', 'P1', 'TRUE', 'IDLE', '2');
INSERT INTO `parking_manage` VALUES ('2', 'P2', 'TRUE', 'IDLE', '2');
INSERT INTO `parking_manage` VALUES ('3', 'P3', 'FALSE', 'IDLE', '2');
INSERT INTO `parking_manage` VALUES ('4', 'P4', 'FALSE', 'IDLE', '2');
INSERT INTO `parking_manage` VALUES ('5', 'P5', 'FALSE', 'IDLE', '2');
INSERT INTO `parking_manage` VALUES ('6', 'P6', 'FALSE', 'IDLE', '2');
INSERT INTO `parking_manage` VALUES ('7', 'P7', 'FALSE', 'IDLE', '2');

-- ----------------------------
-- Table structure for pre_search_task_feedback_table
-- ----------------------------
DROP TABLE IF EXISTS `pre_search_task_feedback_table`;
CREATE TABLE `pre_search_task_feedback_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `task_id` int(11) DEFAULT NULL,
  `task_from` varchar(50) DEFAULT '',
  `task_to` varchar(50) DEFAULT '',
  `priority` varchar(50) DEFAULT '',
  `agv_type` varchar(50) DEFAULT '',
  `agv_id` int(11) DEFAULT NULL,
  `task_type` varchar(50) DEFAULT '',
  `task_status` varchar(50) DEFAULT NULL,
  `error_info` varchar(500) DEFAULT NULL,
  `time_stamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of pre_search_task_feedback_table
-- ----------------------------

-- ----------------------------
-- Table structure for pre_search_task_in_table
-- ----------------------------
DROP TABLE IF EXISTS `pre_search_task_in_table`;
CREATE TABLE `pre_search_task_in_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `task_id` int(11) DEFAULT NULL,
  `task_from` varchar(50) DEFAULT '',
  `task_to` varchar(50) DEFAULT '',
  `priority` varchar(50) DEFAULT '',
  `agv_type` varchar(50) DEFAULT '',
  `agv_id` int(11) DEFAULT NULL,
  `task_type` varchar(50) DEFAULT '',
  `task_status` varchar(50) DEFAULT NULL,
  `error_info` varchar(500) DEFAULT NULL,
  `time_stamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of pre_search_task_in_table
-- ----------------------------

-- ----------------------------
-- Table structure for s_confirm_station_status
-- ----------------------------
DROP TABLE IF EXISTS `s_confirm_station_status`;
CREATE TABLE `s_confirm_station_status` (
  `ID` int(11) NOT NULL,
  `STATION_NAME` varchar(255) DEFAULT NULL,
  `AGV_ID` int(11) DEFAULT NULL,
  `STATUS` varchar(255) DEFAULT NULL,
  `ENTERDATE` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of s_confirm_station_status
-- ----------------------------
INSERT INTO `s_confirm_station_status` VALUES ('1', 'A-CONFIRM', '64', 'IDLE', '2021-08-31 16:51:39');
INSERT INTO `s_confirm_station_status` VALUES ('2', 'X-CONFIRM', '62', 'IDLE', '2021-08-28 21:35:30');
INSERT INTO `s_confirm_station_status` VALUES ('3', 'B-CONFIRM', '65', 'IDLE', '2021-08-31 15:02:40');

-- ----------------------------
-- Table structure for s_equip_station_status
-- ----------------------------
DROP TABLE IF EXISTS `s_equip_station_status`;
CREATE TABLE `s_equip_station_status` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `storage_name` varchar(255) NOT NULL COMMENT '库位名称',
  `storage_type` varchar(255) DEFAULT NULL,
  `storage_row` int(255) DEFAULT NULL COMMENT '行',
  `storage_column` int(255) DEFAULT NULL COMMENT '列',
  `storage_status` varchar(255) DEFAULT '0' COMMENT '状态',
  `resource_status` varchar(255) DEFAULT NULL COMMENT '资源状态(预定、未预定)',
  PRIMARY KEY (`id`,`storage_name`) USING BTREE,
  KEY `storage_name` (`storage_name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of s_equip_station_status
-- ----------------------------
INSERT INTO `s_equip_station_status` VALUES ('1', 'F9WC-1-1', 'EQUIP', '1', '1', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('2', 'F9WC-1-2', 'EQUIP', '1', '2', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('3', 'F9WC-2', 'EQUIP', '1', '3', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('4', 'F9WC-3-1', 'EQUIP', '1', '4', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('5', 'F9WC-3-2', 'EQUIP', '1', '5', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('6', 'F9WC-4', 'EQUIP', '1', '6', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('7', 'F9WC-5-1', 'EQUIP', '1', '7', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('8', 'F9WC-5-2', 'EQUIP', '1', '8', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('9', 'F9WC-6', 'EQUIP', '1', '9', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('10', 'F9WC-7-1', 'EQUIP', '2', '1', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('11', 'F9WC-7-2', 'EQUIP', '2', '2', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('12', 'F9WC-8', 'EQUIP', '2', '3', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('13', 'F9WC-9-1', 'EQUIP', '2', '4', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('14', 'F9WC-9-2', 'EQUIP', '2', '5', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('15', 'F9WC-10', 'EQUIP', '2', '6', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('16', 'F9WC-11-1', 'EQUIP', '2', '7', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('17', 'F9WC-11-2', 'EQUIP', '2', '8', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('18', 'F9WC-12-1', 'EQUIP', '2', '9', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('19', 'F9WC-12-2', 'EQUIP', '2', '10', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('20', 'F9WC-13-1', 'EQUIP', '3', '1', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('21', 'F9WC-13-2', 'EQUIP', '3', '2', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('22', 'F9WC-14', 'EQUIP', '3', '3', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('23', 'F9WC-15-1', 'EQUIP', '3', '4', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('24', 'F9WC-15-2', 'EQUIP', '3', '5', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('25', 'F9WC-16', 'EQUIP', '3', '6', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('26', 'F9WC-17-1', 'EQUIP', '3', '7', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('27', 'F9WC-17-2', 'EQUIP', '3', '8', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('28', 'F9WC-18-1', 'EQUIP', '3', '9', 'EMPTY', 'IDLE');
INSERT INTO `s_equip_station_status` VALUES ('29', 'F9WC-18-2', 'EQUIP', '3', '10', 'EMPTY', 'IDLE');

-- ----------------------------
-- Table structure for s_equip_storage
-- ----------------------------
DROP TABLE IF EXISTS `s_equip_storage`;
CREATE TABLE `s_equip_storage` (
  `ID` int(11) NOT NULL,
  `EQUIP_NAME` varchar(255) DEFAULT NULL,
  `STORAGE_GROUP` varchar(255) DEFAULT NULL,
  `TRAY_TYPE` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of s_equip_storage
-- ----------------------------
INSERT INTO `s_equip_storage` VALUES ('1', 'F9WC-1-1', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('2', 'F9WC-1-2', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('3', 'F9WC-2', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('4', 'F9WC-3-1', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('5', 'F9WC-3-2', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('6', 'F9WC-4', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('7', 'F9WC-5-1', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('8', 'F9WC-5-2', 'A', '220');
INSERT INTO `s_equip_storage` VALUES ('9', 'F9WC-6', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('10', 'F9WC-11-1', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('11', 'F9WC-11-2', 'A', '220');
INSERT INTO `s_equip_storage` VALUES ('12', 'F9WC-12-1', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('13', 'F9WC-12-2', 'A', '220');
INSERT INTO `s_equip_storage` VALUES ('14', 'F9WC-13-1', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('15', 'F9WC-13-2', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('16', 'F9WC-14', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('17', 'F9WC-15-1', 'A', '220');
INSERT INTO `s_equip_storage` VALUES ('18', 'F9WC-15-2', 'A', '236');
INSERT INTO `s_equip_storage` VALUES ('19', 'F9WC-16', 'A', '220');
INSERT INTO `s_equip_storage` VALUES ('20', 'F9WC-7-1', 'B', '236');
INSERT INTO `s_equip_storage` VALUES ('21', 'F9WC-7-2', 'B', '236');
INSERT INTO `s_equip_storage` VALUES ('22', 'F9WC-8', 'B', '236');
INSERT INTO `s_equip_storage` VALUES ('23', 'F9WC-9-1', 'B', '236');
INSERT INTO `s_equip_storage` VALUES ('24', 'F9WC-9-2', 'B', '220');
INSERT INTO `s_equip_storage` VALUES ('25', 'F9WC-10', 'B', '220');
INSERT INTO `s_equip_storage` VALUES ('26', 'F9WC-17-1', 'B', '236');
INSERT INTO `s_equip_storage` VALUES ('27', 'F9WC-17-2', 'B', '236');
INSERT INTO `s_equip_storage` VALUES ('28', 'F9WC-18-1', 'B', '220');
INSERT INTO `s_equip_storage` VALUES ('29', 'F9WC-18-2', 'B', '220');

-- ----------------------------
-- Table structure for s_storage_station_status
-- ----------------------------
DROP TABLE IF EXISTS `s_storage_station_status`;
CREATE TABLE `s_storage_station_status` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `storage_name` varchar(255) NOT NULL COMMENT '库位名称',
  `tray_type` varchar(255) DEFAULT NULL,
  `storage_type` varchar(255) DEFAULT NULL,
  `storage_group` varchar(255) NOT NULL,
  `storage_row` int(255) NOT NULL COMMENT '行',
  `storage_column` int(255) DEFAULT NULL COMMENT '列',
  `storage_status` varchar(255) DEFAULT '0' COMMENT '状态',
  `resource_status` varchar(255) DEFAULT NULL COMMENT '资源状态(预定、未预定)',
  PRIMARY KEY (`id`,`storage_name`) USING BTREE,
  KEY `storage_name` (`storage_name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=65 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of s_storage_station_status
-- ----------------------------
INSERT INTO `s_storage_station_status` VALUES ('1', 'A1', '236', 'AREA', 'A', '1', '1', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('2', 'A2', '236', 'AREA', 'A', '1', '2', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('3', 'A3', '236', 'AREA', 'A', '1', '3', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('4', 'A4', '236', 'AREA', 'A', '1', '4', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('5', 'A5', '236', 'AREA', 'A', '1', '5', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('6', 'A6', '236', 'AREA', 'A', '1', '6', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('7', 'A7', '236', 'AREA', 'A', '1', '7', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('8', 'A8', '236', 'AREA', 'A', '1', '8', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('9', 'A9', '236', 'TRAY', 'A', '1', '9', 'EMPTY', 'RESERVE');
INSERT INTO `s_storage_station_status` VALUES ('10', 'A10', '236', 'TRAY', 'A', '1', '10', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('11', 'A11', '236', 'TRAY', 'A', '1', '11', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('12', 'A12', '236', 'TRAY', 'A', '1', '12', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('13', 'B1', '236', 'AREA', 'A', '2', '1', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('14', 'B2', '236', 'AREA', 'A', '2', '2', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('15', 'B3', '236', 'AREA', 'A', '2', '3', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('16', 'B4', '236', 'AREA', 'A', '2', '4', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('17', 'B5', '236', 'AREA', 'A', '2', '5', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('18', 'B6', '236', 'AREA', 'A', '2', '6', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('19', 'B7', '236', 'AREA', 'A', '2', '7', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('20', 'B8', '236', 'AREA', 'A', '2', '8', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('21', 'B9', '236', 'AREA', 'A', '2', '9', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('22', 'B10', '236', 'AREA', 'A', '2', '10', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('23', 'B11', '236', 'AREA', 'A', '2', '11', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('24', 'B12', '236', 'TRAY', 'A', '2', '12', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('25', 'B13', '236', 'TRAY', 'A', '2', '13', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('26', 'B14', '236', 'TRAY', 'A', '2', '14', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('27', 'B15', '220', 'TRAY', 'A', '2', '15', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('28', 'B16', '220', 'TRAY', 'A', '2', '16', 'EMPTY', 'RESERVE');
INSERT INTO `s_storage_station_status` VALUES ('29', 'C1', '236', 'AREA', 'A', '3', '1', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('30', 'C2', '236', 'AREA', 'A', '3', '2', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('31', 'C3', '236', 'AREA', 'A', '3', '3', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('32', 'C4', '236', 'AREA', 'A', '3', '4', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('33', 'C5', '236', 'AREA', 'A', '3', '5', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('34', 'C6', '236', 'AREA', 'A', '3', '6', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('35', 'C7', '236', 'AREA', 'A', '3', '7', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('36', 'C8', '236', 'AREA', 'A', '3', '8', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('37', 'C9', '236', 'AREA', 'A', '3', '9', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('38', 'C10', '236', 'AREA', 'A', '3', '10', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('39', 'C11', '236', 'AREA', 'A', '3', '11', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('40', 'C12', '236', 'TRAY', 'A', '3', '12', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('41', 'C13', '236', 'TRAY', 'A', '3', '13', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('42', 'C14', '236', 'TRAY', 'A', '3', '14', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('43', 'C15', '220', 'TRAY', 'A', '3', '15', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('44', 'C16', '220', 'TRAY', 'A', '3', '16', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('45', 'D1', '236', 'AREA', 'B', '4', '1', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('46', 'D2', '236', 'AREA', 'B', '4', '2', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('47', 'D3', '236', 'AREA', 'B', '4', '3', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('48', 'D4', '236', 'AREA', 'B', '4', '4', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('49', 'D5', '236', 'AREA', 'B', '4', '5', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('50', 'D6', '236', 'AREA', 'B', '4', '6', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('51', 'D7', '236', 'AREA', 'B', '4', '7', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('52', 'D8', '236', 'AREA', 'B', '4', '8', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('53', 'D9', '236', 'AREA', 'B', '4', '9', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('54', 'D10', '236', 'AREA', 'B', '4', '10', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('55', 'D11', '236', 'AREA', 'B', '4', '11', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('56', 'D12', '236', 'AREA', 'B', '4', '12', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('57', 'D13', '236', 'AREA', 'B', '4', '13', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('58', 'D14', '236', 'AREA', 'B', '4', '14', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('59', 'D15', '220', 'AREA', 'B', '4', '15', 'FULL', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('60', 'D16', '236', 'TRAY', 'B', '4', '16', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('61', 'D17', '236', 'TRAY', 'B', '4', '17', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('62', 'D18', '236', 'TRAY', 'B', '4', '18', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('63', 'D19', '220', 'TRAY', 'B', '4', '19', 'EMPTY', 'IDLE');
INSERT INTO `s_storage_station_status` VALUES ('64', 'D20', '220', 'TRAY', 'B', '4', '20', 'EMPTY', 'IDLE');

-- ----------------------------
-- Table structure for task_feedback_table
-- ----------------------------
DROP TABLE IF EXISTS `task_feedback_table`;
CREATE TABLE `task_feedback_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `task_id` int(11) DEFAULT NULL,
  `task_from` varchar(50) DEFAULT '',
  `task_to` varchar(50) DEFAULT '',
  `priority` varchar(50) DEFAULT '',
  `agv_type` varchar(50) DEFAULT '',
  `agv_id` int(11) DEFAULT NULL,
  `task_type` varchar(50) DEFAULT '',
  `task_status` varchar(50) DEFAULT NULL,
  `error_info` varchar(500) DEFAULT NULL,
  `time_stamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of task_feedback_table
-- ----------------------------

-- ----------------------------
-- Table structure for task_in_history
-- ----------------------------
DROP TABLE IF EXISTS `task_in_history`;
CREATE TABLE `task_in_history` (
  `task_id` int(11) NOT NULL AUTO_INCREMENT,
  `task_from` varchar(50) DEFAULT '',
  `task_to` varchar(50) DEFAULT '',
  `priority` varchar(50) DEFAULT '',
  `agv_type` varchar(50) DEFAULT '',
  `task_type` varchar(50) DEFAULT NULL,
  `timestamp` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `task_extra_param` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`task_id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of task_in_history
-- ----------------------------

-- ----------------------------
-- Table structure for task_in_table
-- ----------------------------
DROP TABLE IF EXISTS `task_in_table`;
CREATE TABLE `task_in_table` (
  `task_id` int(11) NOT NULL AUTO_INCREMENT,
  `task_from` varchar(50) DEFAULT '',
  `task_to` varchar(50) DEFAULT '',
  `priority` varchar(50) DEFAULT '',
  `agv_type` varchar(50) DEFAULT '',
  `task_type` varchar(50) DEFAULT '',
  `auto_dispatch` int(11) DEFAULT NULL,
  `agv_id` int(11) DEFAULT NULL,
  `task_extra_param_type` int(11) DEFAULT NULL,
  `task_extra_param` varchar(255) DEFAULT '',
  PRIMARY KEY (`task_id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of task_in_table
-- ----------------------------

-- ----------------------------
-- Table structure for task_op_interface
-- ----------------------------
DROP TABLE IF EXISTS `task_op_interface`;
CREATE TABLE `task_op_interface` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `object` varchar(255) DEFAULT NULL,
  `agv_id` int(11) DEFAULT NULL,
  `task_id` int(11) DEFAULT NULL,
  `op_code` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=103 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of task_op_interface
-- ----------------------------
DROP TRIGGER IF EXISTS `只获取允许进入的库位的工单_copy1`;
DELIMITER ;;
CREATE TRIGGER `只获取允许进入的库位的工单_copy1` BEFORE INSERT ON `kh_order_info_copy1` FOR EACH ROW BEGIN

DECLARE storage_is_open INT(11);

    IF(NEW.`STATUS` = 'NEW')
    THEN

SET storage_is_open=(SELECT COUNT(*) FROM s_equip_station_status WHERE storage_name=NEW.`START` AND storage_status="FULL");

				IF(storage_is_open = 0)
					THEN 
signal sqlstate '45000';
				END IF;
    END IF;
END
;;
DELIMITER ;
DROP TRIGGER IF EXISTS `只允许REVOKE状态为NEW的任务_copy1`;
DELIMITER ;;
CREATE TRIGGER `只允许REVOKE状态为NEW的任务_copy1` BEFORE UPDATE ON `kh_order_info_copy1` FOR EACH ROW BEGIN
    IF(NEW.`STATUS` = 'REVOKE' AND OLD.`STATUS` != 'NEW')
    THEN
signal sqlstate '45000';
    END IF;
END
;;
DELIMITER ;
