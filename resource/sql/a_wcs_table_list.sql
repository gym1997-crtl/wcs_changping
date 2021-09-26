/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50721
Source Host           : localhost:3306
Source Database       : wcs_zc9

Target Server Type    : MYSQL
Target Server Version : 50721
File Encoding         : 65001

Date: 2021-09-26 10:17:35
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
