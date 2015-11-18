-- MySQL Script generated by MySQL Workbench
-- Qua 11 Nov 2015 07:50:07 BRT
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema projetocpp
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema projetocpp
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `projetocpp` DEFAULT CHARACTER SET utf8 ;
USE `projetocpp` ;

-- -----------------------------------------------------
-- Table `projetocpp`.`employees`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `projetocpp`.`employees` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(60) NOT NULL,
  `age` INT NOT NULL,
  `salary` DOUBLE NOT NULL,
  `role` VARCHAR(45) NOT NULL,
  `email` VARCHAR(45) NOT NULL,
  `endereco` VARCHAR(200) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `projetocpp`.`products`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `projetocpp`.`products` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(60) NOT NULL,
  `purchaseprice` INT NOT NULL,
  `saleprice` INT NOT NULL,
  `quantity` INT NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `projetocpp`.`users`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `projetocpp`.`users` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(45) NOT NULL,
  `password` CHAR(128) NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;