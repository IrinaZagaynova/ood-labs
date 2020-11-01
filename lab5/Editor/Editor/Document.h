#pragma once
#include "History.h"
#include "IDocument.h"
#include "CommandSink.h"
#include <vector>

class CDocument : public IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		optional<size_t> position = none) override;

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images 
	// под автоматически сгенерированным именем
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none) override;

	// Возвращает количество элементов в документе
	size_t GetItemsCount()const override;

	// Доступ к элементам изображения
	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	// Удаляет элемент из документа
	void DeleteItem(size_t index) override;

	// Возвращает заголовок документа
	std::string GetTitle()const override;
	// Изменяет заголовок документа
	void SetTitle(const std::string& title) override;

	// Сообщает о доступности операции Undo
	bool CanUndo()const override;
	// Отменяет команду редактирования
	void Undo() override;

	// Сообщает о доступности операции Redo
	bool CanRedo()const override;
	// Выполняет отмененную команду редактирования
	void Redo() override;

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	void Save(const Path& path)const override;

private:
	std::string EncodeToHtml(const std::string& text) const;

	std::vector<CDocumentItem> m_items;
	std::string m_title;
	CHistory m_history;
};