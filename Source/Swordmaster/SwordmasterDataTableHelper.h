#pragma once

namespace SwordmasterDataTableHelper
{
	template <typename RowType, typename ValueType, typename F>
	static RowType* BinarySearchBy(TArray<RowType*> Rows, const ValueType& Value, F KeySelector)
	{
		int32 Index = Algo::BinarySearchBy(Rows, Value, KeySelector);
		return Index != INDEX_NONE ? Rows[Index] : nullptr;
	}

	template <typename RowType, typename ValueType, typename F>
	static RowType* BinarySearchBy(UDataTable* DataTable, const ValueType& Value, F KeySelector)
	{
		TArray<RowType*> Rows;
		DataTable->GetAllRows(TEXT(""), Rows);
		return BinarySearchBy(Rows, Value, KeySelector);
	}
}
