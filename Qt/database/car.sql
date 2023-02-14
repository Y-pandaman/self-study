/*
 Navicat Premium Data Transfer

 Source Server         : MySQl
 Source Server Type    : MySQL
 Source Server Version : 80027
 Source Host           : localhost:3306
 Source Schema         : car

 Target Server Type    : MySQL
 Target Server Version : 80027
 File Encoding         : 65001

 Date: 21/10/2021 15:49:00
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for brand
-- ----------------------------
DROP TABLE IF EXISTS `brand`;
CREATE TABLE `brand`  (
  `id` int(0) NOT NULL AUTO_INCREMENT,
  `factory` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `price` int(0) NULL DEFAULT NULL,
  `sum` int(0) NULL DEFAULT NULL,
  `sell` int(0) NULL DEFAULT NULL,
  `last` int(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of brand
-- ----------------------------
INSERT INTO `brand` VALUES (1, '一汽大众', '奥迪A6', 36, 50, 8, 42);
INSERT INTO `brand` VALUES (2, '一汽大众', '捷达', 10, 80, 4, 76);
INSERT INTO `brand` VALUES (3, '一汽大众', '奔驰', 83, 40, 6, 34);
INSERT INTO `brand` VALUES (4, '二汽神龙', '毕加索', 39, 50, 6, 44);
INSERT INTO `brand` VALUES (5, '二汽神龙', '富康', 28, 60, 5, 55);
INSERT INTO `brand` VALUES (6, '二汽神龙', '标致307', 27, 70, 4, 66);
INSERT INTO `brand` VALUES (7, '上海大众', '桑塔纳', 25, 75, 2, 73);
INSERT INTO `brand` VALUES (8, '上海大众', '帕萨特', 27, 65, 10, 75);

-- ----------------------------
-- Table structure for factory
-- ----------------------------
DROP TABLE IF EXISTS `factory`;
CREATE TABLE `factory`  (
  `id` int(0) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of factory
-- ----------------------------
INSERT INTO `factory` VALUES (1, '请选择厂家');
INSERT INTO `factory` VALUES (2, '一汽大众');
INSERT INTO `factory` VALUES (3, '二汽神龙');
INSERT INTO `factory` VALUES (4, '上海大众');

SET FOREIGN_KEY_CHECKS = 1;
